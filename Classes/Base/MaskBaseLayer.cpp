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
    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(0,0);
    auto blackItem = MenuItem::create();
    blackItem->setPosition(visibleSize.width/2,visibleSize.height/2);
    blackItem->setContentSize(visibleSize);//设置大小为整个屏幕的大小
    auto blackMenu = Menu::create(blackItem,NULL);
    blackMenu->setPosition(Point::ZERO);
    blackMenu->setAnchorPoint(Point::ZERO);
    this->addChild(blackMenu,MASK_BASE_LAYER);
    return result;
}