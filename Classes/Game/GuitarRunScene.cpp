//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GuitarRunScene.h"
//#include "ChordRunLayer.h"
//#include "FingerRunLayer.h"
#include "POPTGlobal.h"
#include "PlayRunLayer.h"
#include "POPTStringUtils.h"

//界面总高度比例
float visbleHeight;
//游戏主画面占比
    float gameProprotion;
//创建场景
Scene *GuitarRun::createScene(){
    auto scene=Scene::create();
    auto layer = GuitarRun::create();
    visbleHeight = 1.0f;
    //音乐信息
  
    //初始化游戏界面
//    string type = poptGlobal->gni->getType();
    string title;
    //C代表和弦界面 F代表指弹界面 S代表新界面

    gameProprotion = 0.8f;
    auto musicModel = poptGlobal->gni->getMusicModel();
    auto runLayer = layer->startFingerMusic(musicModel,gameProprotion);
    title= musicModel->getTitle();
    
    runLayer->setName("runLayer");
    layer->addChild(runLayer,1);
    
    poptGlobal->runLayer = runLayer;

    //剩下的比例
    float resultPorprotion = visbleHeight-gameProprotion;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sideHeight = visibleSize.height*resultPorprotion/2;
    //加载界面顶部内容
    layer->loadTopFrame(title,sideHeight);
    //加载界面底部内容
    layer->loadFootFrame(sideHeight);

    //初始化参数
    layer->initialise();

    scene->addChild(layer);
    
    return scene;
}
//初始化
void GuitarRun::initialise(){
    
    this->setBackground();
    //节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game/base/snare.caf");
    for (int i=1; i<8; i++) {
        string scaleFileName ="audio/scale/"+POPTStringUtils::intToString(i)+".mp3";
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(scaleFileName.c_str());
    }
    isPause =false;
    musicIsOver=false;
    startAnimation();
    time_now = 0.0f;
}

//加载头部组件
void GuitarRun::loadTopFrame(string title,float height){
    //设置黑色背景
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("game/base/sideBg.png");
    bg->setPreferredSize(Size(visibleSize.width,height));
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(0,visibleSize.height-height);
    this->addChild(bg,2);
    
    //设置歌曲名
    title = "歌曲："+title;
    auto label = Label::createWithTTF(title, "fonts/yuanti.ttf", 15);
    label->setPosition( label->getContentSize().width,height-label->getContentSize().height);
    bg->addChild(label);
 
    //主菜单按钮
    ui::Button *menuBtn = ui::Button::create("game/base/menuBtnNormal.png","game/base/menuBtnSelect.png");
    menuBtn->setAnchorPoint(Vec2::ZERO);
    menuBtn->setPosition(Vec2(visibleSize.width-menuBtn->getContentSize().width,height-menuBtn->getContentSize().height));
    menuBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::menuControll, this,nullptr));
    bg->addChild(menuBtn);
}

//加载底部组件
void GuitarRun::loadFootFrame(float height){
    
    //设置背景
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("game/base/sideBg.png");
    bg->setPreferredSize(Size(visibleSize.width,height));
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg,2);
    
    //时间轴
    slider = POPTSlider::create("game/base/sliderTrack.png", "game/base/sliderProgress.png", "game/base/sliderThumb.png",false);
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime);
    slider->setPosition(Vec2(visibleSize.width/2,height/2));
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GuitarRun::sliderChanged),Control::EventType::VALUE_CHANGED);
    slider->setDelegate(this);
    
    bg->addChild(slider);
    
    float startX = visibleSize.width/2 - slider->getContentSize().width/2;
    float endX =visibleSize.width/2 + slider->getContentSize().width/2;
    
    //暂停
    pauseBtn = ui::Button::create("game/base/pause.png");
    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    pauseBtn->setScale(0.8);
    float pauseBtnWidth = pauseBtn->getContentSize().width;
    startX-=pauseBtnWidth;
    pauseBtn->setPosition(Vec2(startX,height/2));
    bg->addChild(pauseBtn);
    
    //录制
    ui::Button *recordBtn = ui::Button::create("game/base/record.png");
    recordBtn->setScale(0.8);
    float recordBtnWidth = recordBtn->getContentSize().width;
    startX-= recordBtnWidth;
    recordBtn->setPosition(Vec2(startX,height/2));
    bg->addChild(recordBtn);

    //时间信息
    endX = endX+40;
    string text = "00:00";
    time = Label::createWithTTF(text, "fonts/yuanti.ttf", 15);
    time->setPosition(endX,height/2);
    bg->addChild(time);
    
    //小节信息
    endX = endX+time->getContentSize().width+20;
    chordInfo = Label::createWithTTF("", "fonts/yuanti.ttf", 15);
    chordInfo->setPosition(endX,height/2);
    bg->addChild(chordInfo);
    
}

//主菜单按钮
void GuitarRun::menuControll(cocos2d::Ref *ref,MusicMenu* mm){
    //暂停游戏
    if(!isPause){
        pauseGame();
        pauseBtn->loadTextureNormal("game/base/play.png");
    }
    float nowTime = slider->getValue();
    auto auditionLayer= AuditionLayer::createAuditionLayer(nowTime);
    poptGlobal->runLayer->audition(true);
    this->addChild(auditionLayer,5);
}

//移动时间轴定时任务的方法
void GuitarRun::moveSlider(float at){
    time_now+=1;
    if(!slider->isSelected()){
        slider->setValue(time_now);
    }

}

//游戏开始时的3秒动画
void GuitarRun::startAnimation(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    auto clip = ClippingNode::create();
    clip->setInverted(true);
    clip->setAlphaThreshold(0);
    clip->setTag(1);
    this->addChild(clip,10);
    auto layerColor = LayerColor::create(Color4B(0,0,0,150));
    clip->addChild(layerColor,1);
    
    //倒计时动画
    SpriteFrame *startSpriteFrame = SpriteFrame::create("game/base/3.png", Rect(0,0,100,100));
    
    Sprite *startSprite = Sprite::createWithSpriteFrame(startSpriteFrame);
    
    startSprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    layerColor->addChild(startSprite,2);
    Animation *animation = Animation::create();
    for (int i=3; i>=1; i--) {
        __String *frameName = __String::createWithFormat("game/base/%d.png",i);
        log("frameName:%s",frameName->getCString());
        SpriteFrame *spriteFrame = SpriteFrame::create(frameName->getCString(), Rect(0,0,100,100));
        animation->addSpriteFrame(spriteFrame);
    }
    auto l = poptGlobal->runLayer;
    animation->setDelayPerUnit(0.9);
    Animate *action = Animate::create(animation);
    Sequence *startSq = Sequence::create(action,CallFunc::create([this,layerColor,startSprite,l](){
        layerColor->removeChild(startSprite);
        if(l){
            slider->startSliderMove(true);
            l->endAnimationSetting();
            this->removeChildByTag(1);
        }
    }), NULL);
    startSprite->runAction(startSq);
    
    auto nodef = Node::create();//创建模版
    auto close = Sprite::create();//这里使用的是close的那个图标
    nodef->addChild(close);//在模版上添加精灵
    nodef->setPosition(Point(visibleSize.width/2,visibleSize.height/2));//设置的坐标正好是在close button的坐标位置上
    clip->setStencil(nodef);//设置模版
    
    //创建一个全屏的按钮，阻止触摸事件
    auto blackItem = MenuItem::create();
    blackItem->setPosition(visibleSize.width/2,visibleSize.height/2);
    blackItem->setContentSize(visibleSize);//设置大小为整个屏幕的大小
    
    auto blackMenu = Menu::create(blackItem,NULL);
    blackMenu->setPosition(Point::ZERO);
    blackMenu->setAnchorPoint(Point::ZERO);
    layerColor->addChild(blackMenu,100);

}

//暂停按钮
void GuitarRun::pauseControll(cocos2d::Ref *ref, bool flag){
    log("pause controll");
    ui::Button* btn= (ui::Button *)ref;
    if(!isPause){
        this->pauseGame();
        btn->loadTextureNormal("game/base/play.png");
    }else{
        this->resumeGame();
        btn->loadTextureNormal("game/base/pause.png");
    }
    isPause = !isPause;
}

//暂停
void GuitarRun::pauseGame(){
//    poptGlobal->runLayer->onExit();
    
    poptGlobal->runLayer->sectionPause();
    slider->pause();
    this->getScheduler()->pauseTarget(this);
}
//继续
void GuitarRun::resumeGame(){
//    poptGlobal->runLayer->onEnter();
    poptGlobal->runLayer->sectionResume();
    slider->resume();
    this->getScheduler()->resumeTarget(this);
}


//开始指弹界面
RunLayer* GuitarRun::startFingerMusic(MusicModel *musicModel,float proportion){
    auto runLayer = PlayRunLayer::createPlayRunLayer(musicModel,proportion);
    return runLayer;
}

//设置背景
void GuitarRun::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("base/background.png");
    sprite->setOpacity(200); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}

//返回关卡界面
void GuitarRun::goBack(cocos2d::Ref *sender){
    if(poptGlobal->runLayer){
        poptGlobal->runLayer->stopMusic();
    }
    isPause =false;
    
    //去掉节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("game/base/snare.caf");
    for (int i=1; i<8; i++) {
        string scaleFileName ="audio/scale/"+POPTStringUtils::intToString(i)+".mp3";
        CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect(scaleFileName.c_str());
    }

    poptGlobal->runLayer = nullptr;
    Director::getInstance()->popScene();
}

//时间轴改变
void GuitarRun::sliderChanged(Ref *ref,Control::EventType controllEvent){
    float value = slider->getValue();
    if(slider->isSelected()){
        //拖动到定位
        int musicIndex = (int)value/poptGlobal->runLayer->gameConfig->unitTime;
        value = musicIndex * poptGlobal->runLayer->gameConfig->unitTime;
        //小节信息
        chordInfo->setString(poptGlobal->runLayer->getMusicalChord(musicIndex));
    }
    int value_int = ceil(value);
    int minute = value_int/60;
    int sec = value_int%60;
    
    string minute_str = minute>=10 ? StringUtils::format("%d",minute): StringUtils::format("0%d",minute);
    string sec_str=sec>=10 ? StringUtils::format("%d",sec) : StringUtils::format("0%d",sec);
    string time_str = minute_str+":"+sec_str;
    time->setString(time_str);
}

//结束层的“重新开始”按钮
void GuitarRun::endRestartCallback(){
    musicIsOver=false;
    this->removeChildByTag(4);
    poptGlobal->runLayer->stopMusic();

    time_now = 0.0f;
    slider->setValue(time_now);
    removeChildByName("runLayer");
    
//    string type = poptGlobal->gni->getType();

    RunLayer* runLayer;
    auto musicModel = poptGlobal->gni->getMusicModel();
    runLayer = startFingerMusic(musicModel,gameProprotion);
    runLayer->setName("runLayer");
    this->addChild(runLayer,1);
    
    poptGlobal->runLayer = runLayer;
    startAnimation();

    schedule(schedule_selector(GuitarRun::moveSlider), 1, kRepeatForever, 3);
}

//结束层的继续
void GuitarRun::endNextCallback(){
    this->removeChildByTag(2);
    resumeGame();
    pauseBtn->loadTextureNormal("game/base/pause.png");
    goBack(nullptr);
    
    //设置关卡信息

    //系统等级
    int curr_level = UserDefault::getInstance()->getIntegerForKey(CURR_LEVEL_KEY);
    //系统节点
    int curr_node = UserDefault::getInstance()->getIntegerForKey(CURR_NODE_KEY);
    
    //游戏等级
    int gameLevel =poptGlobal->gni->getGameLevelInfo()->getLevel();
    //游戏节点
    int gameNode = poptGlobal->gni->getNode();

    vector<GameLevelInfo*> levels = gameLevelSingleton->levels;

    GameLevelInfo* curr_gli = levels[gameLevel-1];
    vector<GameNodeInfo*> nodes = curr_gli->getNodes();
    
    if(gameNode == curr_node && gameLevel == curr_level){
        if(gameNode+1<=nodes.size()){
            UserDefault::getInstance()->setIntegerForKey(CURR_NODE_KEY, gameNode+1);
        }else if(gameLevel+1<=levels.size()){
            UserDefault::getInstance()->setIntegerForKey(CURR_LEVEL_KEY, gameLevel+1);
            UserDefault::getInstance()->setIntegerForKey(CURR_NODE_KEY, 1);
        }
    }

}

void GuitarRun::sliderMoveEnd(Ref* ref){
    //时间轴结束
    
}

