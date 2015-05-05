//
//  GTRect.cpp
//  Test1
//
//  Created by allen on 14-11-27.
//
//

#include "Rhythm.h"

Rhythm *Rhythm::createRhythm(ChordConfig *common,int currentBeat){
    Rhythm *rhythm = new Rhythm();
    if(rhythm && rhythm->initWithFile("game/chord/rhythm.png",common,currentBeat)){
        rhythm->autorelease();
        return rhythm;
    }
    return nullptr;
    CC_SAFE_DELETE(rhythm);
}

bool Rhythm::initWithFile(const string &filename,ChordConfig *common,int currentBeat){
    bool result = Sprite::initWithFile(filename,Rect(0,0,5,common->contentHeight));
    this->setPosition(0,0);
    this->setTag(currentBeat);
    this->setAnchorPoint(Point::ZERO);
    return result;

}

ActionInterval *Rhythm::firstMoveRhythm(ChordConfig *common){
//    log("uw:%f / us:%f  = %f",common->unitWidth,common->unitSpeed,common->unitWidth/common->unitSpeed);
    //每秒钟走的距离
    float min4width = common->unitWidth/common->unitTime;
    //开始时间行走的距离
    float startWidth = common->startTime*min4width;
    //获得开始时间需要的距离
    scanf("%f%f",&startWidth,&common->rhythm_distance);
//    float startDistance =(int)startWidth%(int)common->rhythm_distance;
    
    float startDistance = startWidth;
    
    //获得开始创建的位置
    float createWidth = common->rhythm_distance - startDistance;
    float time = startDistance/min4width;
    this->setPosition(Vec2(createWidth,0));
    return this->move(common, time);
}

ActionInterval *Rhythm::moveRhythm(ChordConfig *common){
    this->setPosition(Vec2(0,0));
    float time = common->rhythm_time;
    return this->move(common, time);
}


ActionInterval *Rhythm::move(ChordConfig *common,float time){
    MoveTo *beginMove = MoveTo::create(time,Vec2(common->rhythm_distance,0));
    return beginMove;
}

ActionInterval *Rhythm::leftMoveRhythm(ChordConfig *common){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int visibleWidth = visibleSize.width;
    float endSpeed= common->unitTime * common->leftUnit;
    
    MoveTo *endMove = MoveTo::create(endSpeed, Vec2(visibleWidth,0));
    FadeOut *out = FadeOut::create(endSpeed);
    Spawn *spawn = Spawn::create(endMove,out,NULL);
    return spawn;

}
