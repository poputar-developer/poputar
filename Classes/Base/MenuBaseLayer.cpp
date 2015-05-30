//
//  PopBaseLayer.cpp
//  poputar
//
//  Created by allen on 15-4-8.
//
//

#include "MenuBaseLayer.h"


MenuBaseLayer::MenuBaseLayer(){

}

void MenuBaseLayer::appear(){
    //层弹出动画
    auto fadeIn = FadeIn::create(1);
    this->runAction(fadeIn);
}

void MenuBaseLayer::disappear(){
    auto fadeOut = FadeOut::create(1);
    this->runAction(fadeOut);
}

void MenuBaseLayer::close(){
    disappear();
}
