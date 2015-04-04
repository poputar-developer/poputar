//
//  FingerRunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "FingerRunLayer.h"
#include "POPTStringUtils.h"
#include "Musical.h"
#include "MusicAnalysis.h"

FingerRunLayer* FingerRunLayer::createFingerRunLayer(MusicInfo *musicInfo){
    FingerRunLayer *layer = new FingerRunLayer();
    if(layer && layer->init4Finger(Color4B(0,0,0,0),musicInfo))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}
//新建音符时用于设置音符当前的tag
int currentMusical;
ValueMapIntKey stringMap;
//获取准备播放的音符
int flag;
//音乐信息中获取的音符信息
ValueVector musicals;
//节奏线集合
Vector<Sprite *> rhythms;


bool FingerRunLayer::init4Finger(const cocos2d::Color4B &&color, MusicInfo *musicInfo){
    fingerConfig = new FingerConfig(visibleSize.width, visibleSize.height*0.7, musicInfo);
    gameConfig = fingerConfig;
    
    bool result =  init(color,musicInfo);

    musicals = fingerConfig->musicInfo->getMusical();
    
    //当前音符
    currentMusical=0;
    //组装界面
    this->loadFrame();
    
    flag = 1;
    
    //节奏线碰撞时的动画效果
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("finger_rhythm_2.png");
    animation->setDelayPerUnit(0.3f);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "rhythm_blink");

    //节拍音效 
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("snare.caf");
    
    schedule(schedule_selector(FingerRunLayer::musicalMove), fingerConfig->rhythm_time, kRepeatForever, fingerConfig->startTime);
    
//    scheduleUpdate();

    return result;
}

void FingerRunLayer::update(float at){
    
    ui::Scale9Sprite *flagRhythm = (ui::Scale9Sprite *)this->getChildByTag(8001);
    //用目标的中间X点和音符的X点来进行判断

    if(this->getChildByTag(flag)){
        Musical* e = (Musical*)this->getChildByTag(flag);
        float rCenterX = flagRhythm->getPositionX() + flagRhythm->getContentSize().width/2;
        float eX = e->getPositionX() + e->getContentSize().width/2;
        
        if(!e->isCollision && rCenterX>=eX){
            ValueVector stringsInfo = e->getStringsInfo();
            for (int i=0; i<stringsInfo.size(); i++) {
                Sprite *r = (Sprite *)this->getChildByTag(8000+stringsInfo.at(i).asInt());
                auto loading = AnimationCache::getInstance()->getAnimation("rhythm_blink");
                auto animate = Animate::create(loading);
                r->runAction(animate);
            }
            e->musicalVoice();
            e->isCollision = true;
            sendDataToBluetooth();
            flag++;
        }
    }
}
//弦之间的距离
float unitHeight;
void FingerRunLayer::loadFrame(){

    
    float unitHeight = fingerConfig->contentHeight/7;
    int stringCount = 6;
    for (int i=0; i<6; i++) {
        float stringHeight = unitHeight*stringCount;
        stringMap[i+1]=Value(stringHeight);
        
        ui::Scale9Sprite *mString = ui::Scale9Sprite::create("finger_string.png");
        mString->setPreferredSize(Size(Vec2(fingerConfig->contentWidth, mString->getContentSize().height)));
        mString->setPosition(Vec2(fingerConfig->contentWidth/2,stringHeight));
        this->addChild(mString,1);
        
        
        auto mRhythm = Sprite::create("finger_rhythm_1.png");
        mRhythm->setPosition(Vec2(fingerConfig->contentWidth-fingerConfig->rhythm_distance, stringHeight));
        mRhythm->setAnchorPoint(Vec2(1,0.5));
        mRhythm->setTag(8000+i+1);
        this->addChild(mRhythm,3);
        rhythms.pushBack(mRhythm);
        
        stringCount-=1;
    }
}

void FingerRunLayer::endAnimationSetting(){
    sendDataToBluetooth();
    currentMusical = 1;
}



void FingerRunLayer::musicalMove(float at){
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("snare.caf",false,6,0,1);
    Musical* musicalSprite;

    if(currentMusical-1<musicals.size()){
        Value musical = musicals.at(currentMusical-1);
        musicalSprite = Musical::createMusical(fingerConfig, musical.asString(),unitHeight);
        
    }else{
        musicalSprite = Musical::createMusical(fingerConfig, "",unitHeight);
    }
    ActionInterval *ai=musicalSprite->musicalMove(fingerConfig);
    Sequence *sequence = Sequence::create(ai,CallFunc::create([this,musicalSprite](){
        //musicalSprite->runLeftAction(fingerConfig);
        this->removeChild(musicalSprite);
    }),NULL);
    musicalSprite->runAction(sequence);
    musicalSprite->setTag(currentMusical);
    this->addChild(musicalSprite,2);

    currMusicals.pushBack(musicalSprite);
    currentMusical +=1;
}

void FingerRunLayer::stopMusic(){
    currentMusical = 0;
    delete fingerConfig;
}

void FingerRunLayer::sendDataToBluetooth(){
    
    if(flag-1<musicals.size()){
        Value musical = musicals.at(flag-1);
        log("%s",musical.asString().c_str());
        MusicAnalysis::getInstance()->sendMusicChar(musical.asString());
    }
}