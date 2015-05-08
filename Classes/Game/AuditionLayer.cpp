//
//  AuditionLayer.cpp
//  poputar
//
//  Created by allen on 15-5-5.
//
//

#include "AuditionLayer.h"
#include "POPTSlider.h"
#include "POPTGlobal.h"
#include "POPTBaseDefine.h"

AuditionLayer* AuditionLayer::createAuditionLayer(float nowTime){
    AuditionLayer *item = new AuditionLayer();
    if(item && item->init()){
        item->autorelease();
        item->loadFrame(nowTime);
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;

}

bool AuditionLayer::init(){
    bool result =  Layer::init();
    this->setPosition(0,0);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(AuditionLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(AuditionLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(AuditionLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return result;
}

void AuditionLayer::loadFrame(float nowTime){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("game/base/menuLayerBg.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);
    
    //时间轴
    auto slider = POPTSlider::create("game/base/sliderTrack.png", "game/base/sliderProgress.png", "game/base/sliderThumb.png",true);
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime);
    slider->setPosition(Vec2(300,200));
//    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(GuitarRun::sliderChanged),Control::EventType::VALUE_CHANGED);
    slider->setDelegate(this);
    slider->setValue(nowTime);
    bg->addChild(slider);
    
    //暂停
    auto pauseBtn = ui::Button::create("game/base/pause.png");
//    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this,true));
    pauseBtn->setScale(0.8);
    pauseBtn->setPosition(Vec2(195,200));
    bg->addChild(pauseBtn);
    
}

void AuditionLayer::sliderMoveEnd(Ref* ref){
    log("slider end");
}

void AuditionLayer::sliderTouchEndCallback(Ref* ref){
     log("touch end");
    auto silder = (POPTSlider*) ref;
    __Float *f = __Float::create(silder->getValue());
    __NotificationCenter::getInstance()->postNotification(POPT_AUDITION_SILDER_POS,f);
}



bool AuditionLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    log("Touch Began");
    return true;
}

void AuditionLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    log("move");
}

void AuditionLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    log("end");
}
