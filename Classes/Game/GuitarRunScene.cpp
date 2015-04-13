//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GuitarRunScene.h"
#include "ChordRunLayer.h"
#include "FingerRunLayer.h"


//创建场景
Scene *GuitarRun::createScene(GameNodeInfo *gni){
    auto scene=Scene::create();
    auto layer = GuitarRun::create();
    //界面总高度比例
    float visbleHeight=1.0f;
    //游戏主画面占比
    float gameProprotion;
    
    //音乐信息
    auto musicInfo = gni->getMusicInfo();
    //初始化游戏界面
    string type = gni->getType();
    //C代表和弦界面 F代表指弹界面
    if(type == "C"){
        gameProprotion = 0.8f;
        layer->startChordMusic(musicInfo,gameProprotion);
    }else if(type=="F"){
        gameProprotion = 0.8f;
        layer->startFingerMusic(musicInfo,gameProprotion);
    }
    //剩下的比例
    float resultPorprotion = visbleHeight-gameProprotion;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sideHeight = visibleSize.height*resultPorprotion/2;
    //加载界面顶部内容
    layer->loadTopFrame(musicInfo,sideHeight);
    //加载界面底部内容
    layer->loadFootFrame(sideHeight);

    //初始化参数
    layer->initialise(gni);

    scene->addChild(layer);
    
    return scene;
}
//初始化
void GuitarRun::initialise(GameNodeInfo* gni){
    
    this->gni = gni;
    this->setBackground();
    //节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("snare.caf");
    
    isPause =false;
    musicMenuDisplay=false;
    speedBase = 1;
    musicIsOver=false;
    startAnimation();
    
    time_now = 0.0f;
    schedule(schedule_selector(GuitarRun::moveSlider), 1, kRepeatForever, 3);
}

//加载头部组件
void GuitarRun::loadTopFrame(MusicInfo* musicInfo,float height){
    //设置黑色背景
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("sideBg.png");
    bg->setPreferredSize(Size(visibleSize.width,height));
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(0,visibleSize.height-height);
    this->addChild(bg,2);
    
    //设置歌曲名
    string title = "歌曲："+musicInfo->getTitle();
    auto label = Label::createWithTTF(title, "fonts/yuanti.ttf", 15);
    label->setPosition( label->getContentSize().width,height-label->getContentSize().height);
    bg->addChild(label);
    
    //音乐控制界面
    auto musicMenu = MusicMenu::createMusicMenu();
    musicMenu->setDelegate(this);
    musicMenu->setAnchorPoint(Vec2(0,0));
    musicMenu->setPosition(Vec2(visibleSize.width-musicMenu->getContentSize().width,visibleSize.height-height));
    this->addChild(musicMenu,1);
    
    //音乐控制按钮
    ui::Button *musicBtn = ui::Button::create("musicBtnNormal.png","musicBtnSelect.png");
    musicBtn->setAnchorPoint(Vec2::ZERO);
    musicBtn->setPosition(Vec2(visibleSize.width-musicMenu->getContentSize().width,height-musicBtn->getContentSize().height));
    musicBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::musicControll, this,musicMenu));
    bg->addChild(musicBtn);
    
    //增加监听 隐藏音乐控制界面
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this,musicMenu](Touch *t ,Event *e){
        //跳转到弹奏页面
        if(!musicMenu->getBoundingBox().containsPoint(t->getLocation()) && musicMenuDisplay){
            this->moveMusicMenu(!musicMenuDisplay, musicMenu);
            musicMenuDisplay = !musicMenuDisplay;
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    //主菜单按钮
    ui::Button *menuBtn = ui::Button::create("menuBtnNormal.png","menuBtnSelect.png");
    menuBtn->setAnchorPoint(Vec2::ZERO);
    menuBtn->setPosition(Vec2(visibleSize.width-musicMenu->getContentSize().width+musicBtn->getContentSize().width,height-menuBtn->getContentSize().height));
    menuBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::menuControll, this,musicMenu));
    bg->addChild(menuBtn);
}

//加载底部组件
void GuitarRun::loadFootFrame(float height){
    
    //设置背景
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("sideBg.png");
    bg->setPreferredSize(Size(visibleSize.width,height));
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg,2);
    
    //时间轴
    slider = POPTSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(runLayer->gameConfig->musicTime+runLayer->gameConfig->endTime);
    slider->setPosition(Vec2(visibleSize.width/2,height/2));
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GuitarRun::sliderChanged),Control::EventType::VALUE_CHANGED);
    //游戏layer
    slider->gameLayer= runLayer;
    slider->setDelegate(this);
    bg->addChild(slider);
    
    float startX = visibleSize.width/2 - slider->getContentSize().width/2;
    float endX =visibleSize.width/2 + slider->getContentSize().width/2;
    
    //暂停
    pauseBtn = ui::Button::create("pause.png");
    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    pauseBtn->setScale(0.8);
    float pauseBtnWidth = pauseBtn->getContentSize().width;
    startX-=pauseBtnWidth;
    pauseBtn->setPosition(Vec2(startX,height/2));
    bg->addChild(pauseBtn);
    
    //录制
    ui::Button *recordBtn = ui::Button::create("record.png");
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

//节奏按钮方法
void GuitarRun::musicControll(cocos2d::Ref *ref,MusicMenu* mm){
    moveMusicMenu(!musicMenuDisplay, mm);
    musicMenuDisplay = !musicMenuDisplay;
}

//主菜单按钮
void GuitarRun::menuControll(cocos2d::Ref *ref,MusicMenu* mm){
    if(musicMenuDisplay){
        moveMusicMenu(!musicMenuDisplay, mm);
        musicMenuDisplay = !musicMenuDisplay;
    }
    //暂停游戏
    if(!isPause){
        pauseGame();
        pauseBtn->loadTextureNormal("play.png");
    }
    //主菜单
    auto mainMenu = GameMenu::createGameMenu();
    mainMenu->setTag(2);
    mainMenu->setDelegate(this);
    this->addChild(mainMenu,5);
}

//移动节奏面板
void GuitarRun::moveMusicMenu(bool moveIn,MusicMenu* mm){
    float height = mm->getContentSize().height;
    Spawn *spawn;
    float time =0.5;
    if(moveIn){
        MoveBy *chordEndMove = MoveBy::create(time, Vec2(0,-height));
        FadeIn *in = FadeIn::create(time);
        spawn = Spawn::create(chordEndMove,in, NULL);
    }else{
        MoveBy *chordEndMove = MoveBy::create(time, Vec2(0,height));
        FadeOut *out = FadeOut::create(time);
        spawn = Spawn::create(chordEndMove,out, NULL);
    }
    mm->runAction(spawn);
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
    SpriteFrame *startSpriteFrame = SpriteFrame::create("1.png", Rect(0,0,100,100));
    
    Sprite *startSprite = Sprite::createWithSpriteFrame(startSpriteFrame);
    
    startSprite->setPosition(visibleSize.width/2,visibleSize.height/2);
    layerColor->addChild(startSprite,2);
    Animation *animation = Animation::create();
    for (int i=3; i>=1; i--) {
        __String *frameName = __String::createWithFormat("%d.png",i);
        log("frameName:%s",frameName->getCString());
        SpriteFrame *spriteFrame = SpriteFrame::create(frameName->getCString(), Rect(0,0,100,100));
        animation->addSpriteFrame(spriteFrame);
    }
    auto l = runLayer;
    animation->setDelayPerUnit(0.9);
    Animate *action = Animate::create(animation);
    Sequence *startSq = Sequence::create(action,CallFunc::create([this,layerColor,startSprite,l](){
        layerColor->removeChild(startSprite);
        if(l){
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
        btn->loadTextureNormal("play.png");
    }else{
        this->resumeGame();
        btn->loadTextureNormal("pause.png");
    }
    isPause = !isPause;
}

//暂停
void GuitarRun::pauseGame(){
    runLayer->onExit();
    this->getScheduler()->pauseTarget(this);
}
//继续
void GuitarRun::resumeGame(){
    runLayer->onEnter();
    this->getScheduler()->resumeTarget(this);
}

//开始和弦界面
void GuitarRun::startChordMusic(MusicInfo *musicInfo,float proportion){
    runLayer = ChordRunLayer::createChordRunLayer(musicInfo,proportion);
    this->addChild(runLayer,1);
}
//开始指弹界面
void GuitarRun::startFingerMusic(MusicInfo *musicInfo,float proportion){
    runLayer = FingerRunLayer::createFingerRunLayer(musicInfo,proportion);
    this->addChild(runLayer,1);
}

//设置背景
void GuitarRun::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("background.png");
    sprite->setOpacity(200); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}

//返回关卡界面
void GuitarRun::goBack(cocos2d::Ref *sender){
    if(runLayer){
        runLayer->stopMusic();
    }
    isPause =false;
    
    //去掉节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("snare.caf");
    
    //速度恢复正常
    speedBase = 1;
    Scheduler* s = Director::getInstance()->getScheduler();
    s->setTimeScale(speedBase);

    runLayer = nullptr;
    Director::getInstance()->popScene();
}

//主菜单-继续 代理方法
void GuitarRun::goOnCallback(cocos2d::Ref *ref){
    this->removeChildByTag(2);
    resumeGame();
    pauseBtn->loadTextureNormal("pause.png");
}

//主菜单-重新开始回调方法
void GuitarRun::restartCallback(cocos2d::Ref *ref){
    this->removeChildByTag(2);
    runLayer->restart(0);
    time_now=0;
    slider->setValue(time_now);
    
    resumeGame();
    pauseBtn->loadTextureNormal("pause.png");
}

//主菜单-返回回调方法
void GuitarRun::goBackCallback(cocos2d::Ref *sender){
    this->removeChildByTag(2);
    resumeGame();
    pauseBtn->loadTextureNormal("pause.png");
    goBack(sender);
}

//速度改变回调方法
void GuitarRun::speedChangeCallback(float speedBase){
    Scheduler* s = Director::getInstance()->getScheduler();
    s->setTimeScale(speedBase);
}

//节拍器声音控制回调
void GuitarRun::metronomePlayCallback(bool isOn){
    runLayer->metronomePlay = isOn;
}

//主音控制回调
void GuitarRun::musicalPlayCallback(bool isOn){
    runLayer->musicalPlay=isOn;
}

//时间轴改变
void GuitarRun::sliderChanged(Ref *ref,Control::EventType controllEvent){
    float value = slider->getValue();
    if(slider->isSelected()){
        //拖动到定位
        int musicIndex = (int)value/runLayer->gameConfig->unitTime;
        value = musicIndex * runLayer->gameConfig->unitTime;
        //小节信息
        chordInfo->setString(runLayer->getMusicalChord(musicIndex));
    }
    int value_int = ceil(value);
    int minute = value_int/60;
    int sec = value_int%60;
    
    string minute_str = minute>=10 ? StringUtils::format("%d",minute): StringUtils::format("0%d",minute);
    string sec_str=sec>=10 ? StringUtils::format("%d",sec) : StringUtils::format("0%d",sec);
    string time_str = minute_str+":"+sec_str;
    time->setString(time_str);
    
    if(!musicIsOver && slider->getMaximumValue() == slider->getValue()){
        musicIsOver = true;
        log("关卡结束");
        unschedule(schedule_selector(GuitarRun::moveSlider));
        runLayer->metronomePlay = false;
        runLayer->musicalPlay=false;
        
        EndLayer* endLayer = EndLayer::createEndLayer();
        endLayer->setTag(4);
        endLayer->setDelegate(this);
        this->addChild(endLayer,99);
    }
}

//松开时间轴的回调方法
void GuitarRun::sliderTouchEndCallback(){
    float value_float = slider->getValue();
    int value_int = ceil(value_float);
    
    float musicalIndex_float = (float)value_int/runLayer->gameConfig->unitTime;
    int musicalIndex = int(musicalIndex_float+0.5);
    
    float musicalValue = runLayer->getMusicalTime(musicalIndex);
    time_now = musicalValue;
    slider->setValue(time_now);
    runLayer->restart(musicalIndex);
    //小节信息设置为空
    chordInfo->setString("");
}

//结束层的重新开始
void GuitarRun::endRestartCallback(){
    musicIsOver=false;
    this->removeChildByTag(4);
    runLayer->restart(0);
    speedBase = 1;
    time_now = 0.0f;
    slider->setValue(time_now);
    startAnimation();

    schedule(schedule_selector(GuitarRun::moveSlider), 1, kRepeatForever, 3);
}

//结束层的继续
void GuitarRun::endNextCallback(){
    this->removeChildByTag(2);
    resumeGame();
    pauseBtn->loadTextureNormal("pause.png");
    goBack(nullptr);
    
    //设置关卡信息

    //系统等级
    int curr_level = UserDefault::getInstance()->getIntegerForKey(CURR_LEVEL_KEY);
    //系统节点
    int curr_node = UserDefault::getInstance()->getIntegerForKey(CURR_NODE_KEY);
    
    //游戏等级
    int gameLevel =gni->getGameLevelInfo()->getLevel();
    //游戏节点
    int gameNode = gni->getNode();
    
    vector<GameLevelInfo*> levels = GameLevelSingleton::getInstance()->getLeves();

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


