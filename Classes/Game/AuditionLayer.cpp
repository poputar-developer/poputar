//
//  AuditionLayer.cpp
//  poputar
//
//  Created by allen on 15-5-5.
//
//

#include "POPTBaseDefine.h"

AuditionLayer* AuditionLayer::createAuditionLayer(string title,float startTime,float allTime){
    AuditionLayer *item = new AuditionLayer();
    if(item && item->initWithColor(Color4B(0,0,0,200))){
        item->autorelease();
        item->title = title;
        item->nowTime = startTime;
        item->allTime = allTime;
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;

}

void AuditionLayer::loadFrame(){
    
    isPause = true;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(0,0);
    
    string titleLabelStr = "正在试听："+title;
    auto titleLabel = Label::createWithTTF(titleLabelStr, "fonts/STHeiti-Light.ttc", 36);
    titleLabel->setColor(Color3B::WHITE);
    titleLabel->setPosition(visibleSize.width/2, visibleSize.height/2+100);
    this->addChild(titleLabel,MASK_WIDGET_LAYER);

    //退出
    auto backBtn = ui::Button::create("game/base/auditionBackBtn.png");
    backBtn->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2-100));
    backBtn->addClickEventListener(CC_CALLBACK_1(AuditionLayer::pauseControll, this));
    backBtn->setTitleText("退出试听");
    backBtn->setTitleFontSize(30);
    backBtn->setTitleColor(Color3B(230,230,230));
    backBtn->addClickEventListener([=](Ref* ref){
        _delegate->auditionBackCallback(ref);
    });
    this->addChild(backBtn,MASK_WIDGET_LAYER);
    
    
    //时间轴
    slider = POPTSlider::create("game/base/sliderTrack.png", "game/base/sliderProgress.png", "game/base/sliderThumb.png");
    slider->setMinimumValue(0.0f);
    slider->setMaximumValue(poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime);
    slider->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    slider->setDelegate(this);
    slider->addTargetWithActionForControlEvents(this, cccontrol_selector(AuditionLayer::sliderChanged),Control::EventType::VALUE_CHANGED);
    slider->setValue(nowTime);
    this->addChild(slider,MASK_WIDGET_LAYER);
    
    //暂停/开始
    pauseBtn = ui::Button::create("game/base/play.png");
    pauseBtn->setPosition(Vec2(visibleSize.width/2-slider->getContentSize().width/2-50,visibleSize.height/2));
    pauseBtn->addClickEventListener(CC_CALLBACK_1(AuditionLayer::pauseControll, this));
    this->addChild(pauseBtn,MASK_WIDGET_LAYER);
    
    //重新开始
    auto restartBtn = ui::Button::create("game/base/restart.png");
    restartBtn->setPosition(Vec2(visibleSize.width/2+slider->getContentSize().width/2+50,visibleSize.height/2));
    restartBtn->addClickEventListener(CC_CALLBACK_1(AuditionLayer::restartControll, this));
    this->addChild(restartBtn,MASK_WIDGET_LAYER);
    
    
    int allTimeValue = ceil(allTime);
    string allTimeStr = POPTHelper::intToTime(allTimeValue);
    auto allTimeLabel = Label::createWithTTF(allTimeStr, "fonts/STHeiti-Light.ttc", 24);
    allTimeLabel->setAnchorPoint(Vec2(1,0.5));
    allTimeLabel->setColor(Color3B::WHITE);
    allTimeLabel->setPosition(visibleSize.width/2+slider->getContentSize().width/2,visibleSize.height/2-20);
    this->addChild(allTimeLabel,MASK_WIDGET_LAYER);
    
    int nowTimeValue = ceil(nowTime);
    string nowTimeStr = POPTHelper::intToTime(nowTimeValue);
    nowTimeLabel = Label::createWithTTF(nowTimeStr, "fonts/STHeiti-Light.ttc", 24);
    nowTimeLabel->setAnchorPoint(Vec2(0,1));
    nowTimeLabel->setColor(Color3B::WHITE);
    nowTimeLabel->setPosition(visibleSize.width/2-slider->getContentSize().width/2,visibleSize.height/2-20);
    this->addChild(nowTimeLabel,MASK_WIDGET_LAYER);

    
}

void AuditionLayer::sliderChanged(cocos2d::Ref *ref, Control::EventType controllEvent){
    if(slider->isSelected()){
        pauseAudition();
    }
}

void AuditionLayer::sliderTouchEndCallback(Ref* ref){
     log("touch end");

    resumeAudition();
    auto slider = (POPTSlider*) ref;
    nowTime = slider->getValue();
    __Float *f = __Float::create(nowTime);
    __NotificationCenter::getInstance()->postNotification(POPT_AUDITION_RESUME,f);
}


//暂停按钮
void AuditionLayer::pauseControll(cocos2d::Ref *ref){
    log("pause controll");
    
    if(!isPause){
        pauseAudition();
    }else{
        resumeAudition();
    }
}

void AuditionLayer::pauseAudition(){
    isPause = true;
    pauseBtn->loadTextureNormal("game/base/play.png");
    //暂停时间轴移动
    //暂定试听层移动
    __NotificationCenter::getInstance()->postNotification(POPT_AUDITION_PAUSE);
    unschedule(schedule_selector(AuditionLayer::moveTime));
}

void AuditionLayer::resumeAudition(){
    isPause = false;
    pauseBtn->loadTextureNormal("game/base/pause.png");
    //开始根据当前时间轴的位置开始播放
    __Float *f = __Float::create(slider->getValue());
    __NotificationCenter::getInstance()->postNotification(POPT_AUDITION_RESUME,f);
    schedule(schedule_selector(AuditionLayer::moveTime), 1, kRepeatForever, 0.000001);
}

void AuditionLayer::moveTime(float at){
    nowTime+=1;
    slider->setValue(nowTime);
    
    nowTimeLabel->setString(POPTHelper::intToTime(ceil(nowTime)));
    if(nowTime>=allTime){
        pauseAudition();
    }
    
}

void AuditionLayer::restartControll(cocos2d::Ref *ref){
    pauseAudition();
}

void AuditionLayer::setDelegate(AuditionLayerDelegate *delegate){
    _delegate = delegate;
}

