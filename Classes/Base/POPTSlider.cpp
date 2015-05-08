//
//  Slider.cpp
//  poputar
//
//  Created by allen on 15-4-6.
//
//

#include "POPTSlider.h"
POPTSlider* POPTSlider::create(const char *bgFile, const char *progressFile, const char *thumbFile,bool drag){
    
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
    pRet->drag = drag;
    pRet->loadTimeInfo();
    return pRet;
}

void POPTSlider::loadTimeInfo(){

}

void POPTSlider::sliderMove(float dt){
    float value = getValue()+moveTime;
    if(value >= getMaximumValue()){
        unschedule(schedule_selector(POPTSlider::sliderMove));
        _delegate->sliderMoveEnd(this);
    }else{
        this->setValue(value);
    }
}

void POPTSlider::startSliderMove(bool flag){
    if(!moving && flag){
        moving = flag;
        schedule(schedule_selector(POPTSlider::sliderMove),moveTime);
    }
}
void POPTSlider::sliderPasue(bool flag){
    if (moving) {
        if (flag) {
            this->pause();
        }else{
            this->resume();
        }
    }
}

void POPTSlider::onTouchEnded(Touch *pTouch, Event *pEvent)
{
    sliderEnded(Vec2::ZERO);
    _delegate->sliderTouchEndCallback(this);
}

void POPTSlider::setDelegate(POPTSliderDelegate *delegate){
    _delegate = delegate;
}

bool POPTSlider::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *pEvent){
    return drag;
}



