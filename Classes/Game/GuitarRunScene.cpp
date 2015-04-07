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
    
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    isPause =false;
    speedBase = 1;
    
    string title = "歌曲："+musicInfo->getTitle();
    auto label = Label::createWithTTF(title, "fonts/manhuati.ttf", 20);
    label->setPosition( label->getContentSize().width,visibleSize.height-label->getContentSize().height);
    this->addChild(label);
    
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

    
    ui::Button *pauseBtn = ui::Button::create("left_btn.png");
    pauseBtn->setAnchorPoint(Vec2::ZERO);
    pauseBtn->setPosition(Vec2(200,100));
    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    //this->addChild(pauseBtn);
    
    slider = POPTSlider::create("sliderTrack.png", "sliderProgress.png", "sliderThumb.png");
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(runLayer->gameConfig->musicTime+runLayer->gameConfig->endTime);
    slider->setScale(2);
    slider->setPosition(Vec2(visibleSize.width/2,30));
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GuitarRun::sliderChanged),Control::EventType::VALUE_CHANGED);
    //游戏layer
    slider->gameLayer= runLayer;
    
    this->addChild(slider);
    
    startAnimation();
    
    time_now = 0.0f;
    
    schedule(schedule_selector(GuitarRun::moveSlider), 1, kRepeatForever, 3);
    
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
    if(!isPause){
        Director::getInstance()->pause();
    }else{
        Director::getInstance()->resume();
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
    this->addChild(runLayer);
}

void GuitarRun::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("xiaoxingxing.png");
    sprite->setOpacity(100); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}

void GuitarRun::goBack(cocos2d::Ref *sender){
    if(runLayer){
        runLayer->stopMusic();
    }
    speedBase = 1;
    isPause =false;
    
    Scheduler* s = Director::getInstance()->getScheduler();
    s->setTimeScale(speedBase);
    runLayer = nullptr;
    Director::getInstance()->popScene();
}
