//
//  RunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "RunLayer.h"


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

    this->startAnimation();

    scheduleUpdate();

    return result;
}
//开始动画方法
void RunLayer::startAnimation(){
    int visibleWidth = visibleSize.width;
    //倒计时动画
    SpriteFrame *startSpriteFrame = SpriteFrame::create("1.png", Rect(0,0,100,100));
    
    Sprite *startSprite = Sprite::createWithSpriteFrame(startSpriteFrame);
    
    startSprite->setPosition(visibleWidth/2,gameConfig->contentHeight/2);
    this->addChild(startSprite,2);
    Animation *animation = Animation::create();
    for (int i=3; i>=1; i--) {
        __String *frameName = __String::createWithFormat("%d.png",i);
        log("frameName:%s",frameName->getCString());
        SpriteFrame *spriteFrame = SpriteFrame::create(frameName->getCString(), Rect(0,0,100,100));
        animation->addSpriteFrame(spriteFrame);
    }
    animation->setDelayPerUnit(0.9);
    Animate *action = Animate::create(animation);
    Sequence *startSq = Sequence::create(action,CallFunc::create([this,startSprite](){
//        currentBeat = 1;
        this->endAnimationSetting();
        this->removeChild(startSprite);
    }), NULL);
    startSprite->runAction(startSq);
    //    startSprite->runAction(action);
    
}
