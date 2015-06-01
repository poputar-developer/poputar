//
//  Slider.cpp
//  poputar
//
//  Created by allen on 15-4-6.
//
//

#include "POPTSlider.h"

POPTSlider* POPTSlider::create(const char *bgFile, const char *progressFile, const char *thumbFile){
    
    Sprite *backgroundSprite      = Sprite::create(bgFile);
    
    Sprite *progressSprite        = Sprite::create(progressFile);
    Sprite *thumbSprite;
    if(thumbFile == nullptr){
        thumbSprite           = Sprite::create();
    }else{
        thumbSprite           = Sprite::create(thumbFile);
    }
    POPTSlider *pRet = new (std::nothrow) POPTSlider();
    pRet->initWithSprites(backgroundSprite, progressSprite, thumbSprite);
    pRet->autorelease();
    return pRet;
}

void POPTSlider::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    sliderEnded(Vec2::ZERO);
    _delegate->sliderTouchEndCallback(this);
}

void POPTSlider::setDelegate(POPTSliderDelegate *delegate){
    _delegate = delegate;
}


