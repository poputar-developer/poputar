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
Scene *GuitarRun::createScene(MusicInfo *musicInfo,GameInfo *gameInfo){
    auto scene=Scene::create();
    auto layer = GuitarRun::create();
    
    string type = gameInfo->getType();
    //C代表和弦界面 F代表指弹界面
    if(type == "C"){
       layer->startChordMusic(musicInfo);
    }else if(type=="F"){
        layer->startFingerMusic(musicInfo);
    }
    
    layer->loadFrame(musicInfo);

    scene->addChild(layer);
    
    return scene;
}

void GuitarRun::loadFrame(MusicInfo *musicInfo){
    
    this->setBackground();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("snare.caf");
    
    isPause =false;
    speedBase = 1;
    
    string title = "歌曲："+musicInfo->getTitle();
    auto label = Label::createWithTTF(title, "fonts/manhuati.ttf", 15);
    label->setPosition( label->getContentSize().width,visibleSize.height-label->getContentSize().height+5);
    this->addChild(label);
    
    
    
    //音乐控制界面
    auto musicMenu = MusicMenu::createMusicMenu();
    musicMenu->setAnchorPoint(Vec2(0,0));
    musicMenu->setPosition(Vec2(200,visibleSize.height));
    this->addChild(musicMenu,5);
    
    
    //音乐控制按钮
    ui::Button *musicBtn = ui::Button::create("musicBtnNormal.png","musicBtnSelect.png");
    musicBtn->setAnchorPoint(Vec2::ZERO);
    musicBtn->setPosition(Vec2(400,visibleSize.height-musicBtn->getContentSize().height));
    musicBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::musicControll, this,musicMenu));
    this->addChild(musicBtn);
    
    //增加监听 隐藏音乐控制界面
    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = [this,musicMenu](Touch *t ,Event *e){
        //跳转到弹奏页面
        if(!musicMenu->getBoundingBox().containsPoint(t->getLocation())){
            this->moveMusicMenu(false, musicMenu);
        }
        
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    //主菜单按钮
    ui::Button *menuBtn = ui::Button::create("menuBtnNormal.png","menuBtnSelect.png");
    menuBtn->setAnchorPoint(Vec2::ZERO);
    menuBtn->setPosition(Vec2(400+musicBtn->getContentSize().width,visibleSize.height-menuBtn->getContentSize().height));
    menuBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::menuControll, this));
    this->addChild(menuBtn);
    
    
    ui::Button *speedUpBtn = ui::Button::create("left_btn.png");
    speedUpBtn->setAnchorPoint(Vec2::ZERO);
    speedUpBtn->setPosition(Vec2(200,200));
    speedUpBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::speedControll, this,true));
    //this->addChild(speedUpBtn,3);
    
    ui::Button *speedUpDown = ui::Button::create("left_btn.png");
    speedUpDown->setAnchorPoint(Vec2::ZERO);
    speedUpDown->setPosition(Vec2(200,100));
    speedUpDown->addClickEventListener(CC_CALLBACK_1(GuitarRun::speedControll, this,false));
    //this->addChild(speedUpDown,3);

    
    ui::Button *recordBtn = ui::Button::create("record.png");
    recordBtn->setAnchorPoint(Vec2::ZERO);
    recordBtn->setPosition(Vec2(30,15));
    recordBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    this->addChild(recordBtn);
    
    ui::Button *pauseBtn = ui::Button::create("pause.png");
    pauseBtn->setAnchorPoint(Vec2::ZERO);
    pauseBtn->setPosition(Vec2(80,15));
    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    this->addChild(pauseBtn);
    
    //时间轴
    slider = POPTSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(runLayer->gameConfig->musicTime+runLayer->gameConfig->endTime);
    slider->setScale(2);
    slider->setPosition(Vec2(visibleSize.width/2,30));
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GuitarRun::sliderChanged),Control::EventType::VALUE_CHANGED);
    //游戏layer
    slider->gameLayer= runLayer;
    slider->setScale(1.2);
    this->addChild(slider);
    
    string text = "00:00";
    auto time = Label::createWithTTF(text, "fonts/manhuati.ttf", 15);
    time->setPosition(520,20);
    this->addChild(time);

    
    startAnimation();
    
    time_now = 0.0f;
    
    schedule(schedule_selector(GuitarRun::moveSlider), 1, kRepeatForever, 3);
    
}

void GuitarRun::musicControll(cocos2d::Ref *ref,MusicMenu* mm){
    moveMusicMenu(true, mm);
}

void GuitarRun::menuControll(cocos2d::Ref *ref){
    //暂停游戏
    Director::getInstance()->pause();
    //主菜单
    auto mainMenu = GameMenu::createGameMenu();
    mainMenu->setTag(2);
    mainMenu->setDelegate(this);
    this->addChild(mainMenu,5);
}

void GuitarRun::moveMusicMenu(bool moveIn,MusicMenu* mm){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Spawn *spawn;
    if(moveIn){
        MoveTo *chordEndMove = MoveTo::create(1, Vec2(mm->getPositionX(),visibleSize.height-mm->getContentSize().height));
        FadeIn *in = FadeIn::create(1);
        spawn = Spawn::create(chordEndMove,in, NULL);
    }else{
        MoveTo *chordEndMove = MoveTo::create(1, Vec2(mm->getPositionX(),visibleSize.height));
        FadeOut *out = FadeOut::create(1);
        spawn = Spawn::create(chordEndMove,out, NULL);
    }
    mm->runAction(spawn);
}


void GuitarRun::sliderChanged(Ref *ref,Control::EventType controllEvent){
    float value = slider->getValue();
    if(slider->isSelected()){
        //拖动到定位
        int muscilIndex = (int)value/runLayer->gameConfig->unitTime;
        time_now = muscilIndex * runLayer->gameConfig->unitTime;
    }
}

void GuitarRun::moveSlider(float at){
    
    time_now+=1;
    if(!slider->isSelected()){
        slider->setValue(time_now);
    }
    
}
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

void GuitarRun::pauseControll(cocos2d::Ref *ref, bool flag){
    log("pause controll");
    ui::Button* btn= (ui::Button *)ref;
    if(!isPause){
        Director::getInstance()->pause();
        btn->loadTextureNormal("play.png");
    }else{
        Director::getInstance()->resume();
        btn->loadTextureNormal("pause.png");
    }
    isPause = !isPause;
}

void GuitarRun::speedControll(cocos2d::Ref *ref,bool speedUp){
    log("speed controll");
    
    Scheduler* s = Director::getInstance()->getScheduler();
    
    if(speedUp) {
        speedBase+=0.5;
    }else{
        speedBase-=0.5;
    }
    s->setTimeScale(speedBase);
}

void GuitarRun::startChordMusic(MusicInfo *musicInfo){
    runLayer = ChordRunLayer::createChordRunLayer(musicInfo);
    this->addChild(runLayer,1);
}

void GuitarRun::startFingerMusic(MusicInfo *musicInfo){
    runLayer = FingerRunLayer::createFingerRunLayer(musicInfo);
    this->addChild(runLayer,1);
}

void GuitarRun::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("background.png");
    sprite->setOpacity(200); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}

void GuitarRun::goBack(cocos2d::Ref *sender){
    if(runLayer){
        runLayer->stopMusic();
    }
    isPause =false;
    
    //去掉节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("snare.caf");
    
    speedBase = 1;
    Scheduler* s = Director::getInstance()->getScheduler();
    s->setTimeScale(speedBase);

    runLayer = nullptr;
    Director::getInstance()->popScene();
}

//主菜单-继续 代理方法
void GuitarRun::goOnCallback(cocos2d::Ref *ref){
    this->removeChildByTag(2);
    Director::getInstance()->resume();
}

//主菜单-重新开始 代理方法
void GuitarRun::restartCallback(cocos2d::Ref *ref){
    this->removeChildByTag(2);
    runLayer->restart(0);
    time_now=0;
    slider->setValue(time_now);
    
    Director::getInstance()->resume();
}

//主菜单-返回 代理方法
void GuitarRun::goBackCallback(cocos2d::Ref *sender){
    this->removeChildByTag(2);
    Director::getInstance()->resume();

    goBack(sender);
}


