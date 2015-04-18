//
//  MaskBaseLayer.cpp
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#include "MaskBaseLayer.h"

bool MaskBaseLayer::initWithColor(const Color4B& color){
    bool result =  LayerColor::initWithColor(color);
    this->setPosition(0,0);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(MaskBaseLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MaskBaseLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MaskBaseLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return result;
}


bool MaskBaseLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    log("Touch Began");
    return true;
}

void MaskBaseLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    log("move");
}

void MaskBaseLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    log("end");
}