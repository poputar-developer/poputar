//
//  BaseLayer.cpp
//  Guitars
//
//  Created by allen on 15-3-24.
//
//

#include "BaseLayer.h"

bool BaseLayer::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();

    
    ui::Button *btn = ui::Button::create("back.png");
    btn->setAnchorPoint(Vec2::ZERO);
    Rect rect = btn->getBoundingBox();
    btn->setPosition(Vec2(visibleSize.width-rect.size.width, visibleSize.height-rect.size.height));
    
    btn->addClickEventListener(CC_CALLBACK_1(BaseLayer::goBack, this));
    
    this->addChild(btn,999);
    
    this->setBackground();
    
    return true;

}

void BaseLayer::goBack(cocos2d::Ref *sender){
    log("baseLayer -- goBack");
    Director::getInstance()->popScene();
}

void BaseLayer::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("background.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
    
}