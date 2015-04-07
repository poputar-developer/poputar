//
//  RunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "RunLayer.h"


bool RunLayer::init(const cocos2d::Color4B &color,MusicInfo *musicInfo){
    bool result =  initWithColor(color);
    //==============设置内容页大小==============
    //    //设置大小
    this->setContentSize(Size(visibleSize.width, gameConfig->contentHeight));
    //    //设置锚点
    this->setAnchorPoint(CCPoint::ZERO);
    float sideHeight = (visibleSize.height-gameConfig->contentHeight)/2;
    //    //设置位置
    this->setPosition(Point(0,sideHeight));

    //this->startAnimation();

    scheduleUpdate();

    return result;
}