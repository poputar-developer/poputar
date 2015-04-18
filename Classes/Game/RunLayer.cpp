//
//  RunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "RunLayer.h"
#include "POPTBaseDefine.h"


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

    metronomePlay=true;
    
    musicalPlay = true;
    
    capoValue = 1.15f;
    
    scheduleUpdate();

    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(RunLayer::metronomeVoiceCallback), POPT_METRONOME_VOICE , NULL);
    
     __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(RunLayer::musicVoiceCallback), POPT_MUSIC_VOICE , NULL);
    
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(RunLayer::capoChangeCallback), POPT_CAPO_VALUE , NULL);
    
    
    return result;
}
void RunLayer::capoChangeCallback(cocos2d::Ref *ref){
    __Float* f = (__Float*) ref;
    capoValue = f->getValue();
}

void RunLayer::metronomeVoiceCallback(cocos2d::Ref *ref){
    __Bool* b = (__Bool*)ref;
    metronomePlay = b->getValue();
}


void RunLayer::musicVoiceCallback(cocos2d::Ref *ref){
    __Bool* b = (__Bool*)ref;
    musicalPlay = b->getValue();
}

RunLayer::~RunLayer(){
    __NotificationCenter::getInstance()->removeObserver(this, POPT_METRONOME_VOICE);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_MUSIC_VOICE);
}