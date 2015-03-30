//
//  FingerRunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "FingerRunLayer.h"
#include "Common.h"
#include "POPTStringUtils.h"
#include "Musical.h"
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

int currentMusical;
ValueMapIntKey stringMap;
bool FingerRunLayer::init4Finger(const cocos2d::Color4B &&color, MusicInfo *musicInfo){

    common = Common::getInstance4Finger(visibleSize.width, visibleSize.height*0.7, musicInfo);
    
    bool result =  init(color,musicInfo);
    //==============设置内容页大小==============

    //当前音符
    currentMusical=0;
    //组装界面
    this->loadFrame();
    //移动速度
    this->speed=3;
    
    schedule(schedule_selector(FingerRunLayer::musicalMove), common->rhythm_time, kRepeatForever, common->startTime);
    
    return result;
}

void FingerRunLayer::loadFrame(){
    float column = common->contentHeight/7;
    int stringCount = 6;
    for (int i=0; i<6; i++) {
        
        float columnHeight = column*stringCount;
        stringMap[i+1]=Value(columnHeight);
        ui::Scale9Sprite *mString = ui::Scale9Sprite::create("finger_string.png");
        mString->setPreferredSize(Size(Vec2(common->contentWidth, mString->getContentSize().height)));
        mString->setPosition(Vec2(common->contentWidth/2,columnHeight));
        this->addChild(mString,1);
        stringCount-=1;
    }
    
    ui::Scale9Sprite *mRhythm = ui::Scale9Sprite::create("finger_rhythm.png");
    mRhythm->setPreferredSize(Size(mRhythm->getContentSize().width, common->contentHeight));
    mRhythm->setPosition(Vec2(common->rhythm_distance, common->contentHeight/2));
    this->addChild(mRhythm,1);
    
}

void FingerRunLayer::endAnimationSetting(){
    currentMusical = 1;
}

void FingerRunLayer::musicalMove(float at){
   
    ValueVector musicals = common->musicInfo->getMusical();
    if(currentMusical<musicals.size()){
        Value musical = musicals.at(currentMusical-1);
        
        vector<string> infos = POPTStringUtils::split(musical.asString(), "@|@");
        map<int,int> charInfo;
        
        for(size_t i=0;i<infos.size();i++){
            string info = infos[i];
            if(info.length()>0){
                vector<string> s = POPTStringUtils::split(info, ":");
                int key = atoi(s[0].data()); //弦位置
                int value = atoi(s[1].data()); //品位置
                
                float y = stringMap[key].asFloat();
                auto musicalSprite = Musical::createMusical("finger_popo.png",key,value,y);
                musicalSprite->setScale(0.5);
                musicalSprite->setPosition(Vec2(0,y));
                musicalSprite->setTag(currentMusical+1);
                musicalSprite->setAnchorPoint(Vec2(1,0.5));
                ActionInterval *ai=musicalSprite->musicalMove(common, speed);
                Sequence *sequence = Sequence::create(ai,CallFunc::create([this,musicalSprite](){
                    ActionInterval *leftAi =musicalSprite->musicalFadeOut(common);
                    Sequence *removeSq=Sequence::create(leftAi,CallFunc::create([this](){
                        //                    this->removeChildByTag(currentMusical-1);
                    }), NULL);
                    musicalSprite->runAction(removeSq);
                }),NULL);
                musicalSprite->runAction(sequence);
                
                this->addChild(musicalSprite,2);
            }
        }
 
    }
    currentMusical +=1;
}

void FingerRunLayer::stopMusic(){
    currentMusical = 0;
}