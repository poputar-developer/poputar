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
    
    Sprite *thumbSprite           = Sprite::create(thumbFile);
    
    POPTSlider *pRet = new (std::nothrow) POPTSlider();
    pRet->initWithSprites(backgroundSprite, progressSprite, thumbSprite);
    pRet->autorelease();
    return pRet;

}

void POPTSlider::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    
    sliderEnded(Vec2::ZERO);
    float value = this->getValue();
    //拖动到的音符位置
    int muscilIndex = (int)value/gameLayer->gameConfig->unitTime;
    gameLayer->restart(muscilIndex);
}