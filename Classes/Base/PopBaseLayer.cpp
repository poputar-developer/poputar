//
//  PopBaseLayer.cpp
//  poputar
//
//  Created by allen on 15-4-8.
//
//

#include "PopBaseLayer.h"


PopBaseLayer::PopBaseLayer(){
}

void PopBaseLayer::appear(){
    //层弹出动画

    auto fadeIn = FadeIn::create(1);

    this->runAction(fadeIn);
}

void PopBaseLayer::disappear(){
    auto fadeOut = FadeOut::create(1);
    this->runAction(fadeOut);
}

void PopBaseLayer::close(){
    disappear();
}
