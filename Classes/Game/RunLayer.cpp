//
//  RunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "RunLayer.h"
#include "POPTBaseDefine.h"


bool RunLayer::init(const cocos2d::Color4B &color){
    bool result =  initWithColor(color);

    //==============设置内容页大小==============
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //设置大小
    this->setContentSize(Size(visibleSize.width, gameConfig->contentHeight));
    //设置锚点
    this->setAnchorPoint(CCPoint::ZERO);
    float sideHeight = (visibleSize.height-gameConfig->contentHeight)/2;
    //设置位置
    this->setPosition(Point(0,sideHeight));
    
    scheduleUpdate();
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(RunLayer::auditionResume), POPT_AUDITION_RESUME , NULL);
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(RunLayer::auditionPause), POPT_AUDITION_PAUSE , NULL);
    
    return result;
}

RunLayer::~RunLayer(){
    __NotificationCenter::getInstance()->removeObserver(this, POPT_AUDITION_RESUME);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_AUDITION_PAUSE);
}