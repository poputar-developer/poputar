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
#include "MusicalBackground.h"

Vector<Musical*> currMusicals;

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
//float minMove;
bool FingerRunLayer::init4Finger(const cocos2d::Color4B &&color, MusicInfo *musicInfo){
    fingerConfig = new FingerConfig(visibleSize.width, visibleSize.height*0.7, musicInfo);
    gameConfig = fingerConfig;
    
    bool result =  init(color,musicInfo);
//    //==============设置内容页大小==============

    //当前音符
    currentMusical=0;
    //组装界面
    this->loadFrame();
    
    schedule(schedule_selector(FingerRunLayer::musicalMove), fingerConfig->rhythm_time, kRepeatForever, fingerConfig->startTime);
    
   
    
//    float time = fingerConfig->rhythm_time;
//    //从开始位置移动到节奏线位置所需时间
//    float moveTime = time * fingerConfig->speedBase;
//    //开始位置到节奏线位置的距离
//    float moveDistance = fingerConfig->rhythm_distance;
//    //每秒移动距离
//    float secMove = moveDistance/moveTime;
//    
//    minMove = secMove/60;
//    log("没秒移动距离：%f",minMove);
    
    scheduleUpdate();
    
    
    
    return result;
}
float bj1X;
float bj2X;
void FingerRunLayer::update(float at){
//增加碰撞检测
    
    ui::Scale9Sprite *mRhythm = (ui::Scale9Sprite *)this->getChildByTag(95);
    for (auto &e:currMusicals) {
        if(!e->isCollision && mRhythm->boundingBox().intersectsRect(e->boundingBox())){
            log("boom!");
            e->musicalVoice();
            e->isCollision = true;
        }
    }
    
//增加竖线
//    MusicalBackground *sp1=(MusicalBackground *)this->getChildByTag(98);
//    MusicalBackground *sp2=(MusicalBackground *)this->getChildByTag(99);
//    
//    
//    MoveBy* mb1 = (MoveBy*)sp1->getActionByTag(1);
//    MoveBy* mb2 = (MoveBy*)sp2->getActionByTag(1);
//    Vec3 newP1 = mb1->getNewPos();
//    Vec3 newP2 = mb2->getNewPos();
//    
//    //log("mb1 new PosX :%f",newP1.x);
//    
//    float distance1 = newP1.x-bj1X;
//    float distance2 = newP2.x-bj2X;
//
//    log("1 current :%f  ----- move  %f",newP1.x,distance1);
//    log("2 current :%f  ----- move  %f",newP2.x,distance2);
//    
//    bj1X =newP1.x;
//    bj2X =newP2.x;
//
//    if(sp1->getPositionX()<=-sp1->getContentSize().width)
//    {
//        sp1->setPosition(Vec2(fingerConfig->contentWidth+distance2,0));
//        sp1->stopActionByTag(1);
//
//        Action* a3 = sp1->MucsicalBackgroundMove(fingerConfig);
//        a3->setTag(1);
//        sp1->runAction(a3);
//
//    }else
//        if(sp2->getPositionX()<=-sp2->getContentSize().width)
//        {
//            sp2->setPosition(Vec2(fingerConfig->contentWidth+distance1,0));
//            sp2->stopActionByTag(1);
//
//            Action* a4 = sp2->MucsicalBackgroundMove(fingerConfig);
//            a4->setTag(1);
//            sp2->runAction(a4);
//        }
    
    //    sp1->setPosition(Vec2(sp1->getPositionX()-minMove,sp1->getPositionY()));
    //    sp2->setPosition(Vec2(sp2->getPositionX()-minMove,sp2->getPositionY()));
    //log("%f",sp2->getPositionX());

}

void FingerRunLayer::loadFrame(){
    ui::Scale9Sprite *mRhythm = ui::Scale9Sprite::create("finger_rhythm.png");
    //设置节奏线大小
    mRhythm->setPreferredSize(Size(mRhythm->getContentSize().width, fingerConfig->contentHeight));
    //设置节奏线位置
    mRhythm->setPosition(Vec2(fingerConfig->contentWidth-fingerConfig->rhythm_distance, fingerConfig->contentHeight/2));
    mRhythm->setTag(95);
    this->addChild(mRhythm,2);
    
    float column = fingerConfig->contentHeight/7;
    int stringCount = 6;
    //和弦区域高度和启始x
    float oneY;
    float sixY;
    for (int i=0; i<6; i++) {
        float columnHeight = column*stringCount;
        stringMap[i+1]=Value(columnHeight);
        ui::Scale9Sprite *mString = ui::Scale9Sprite::create("finger_string.png");
        mString->setPreferredSize(Size(Vec2(fingerConfig->contentWidth, mString->getContentSize().height)));
        mString->setPosition(Vec2(fingerConfig->contentWidth/2,columnHeight));
        this->addChild(mString,1);
        stringCount-=1;
        if(i==5){
            oneY = columnHeight;
        }else if(i==0){
            sixY = columnHeight;
        }
    }
    
//    MusicalBackground *mb1 = MusicalBackground::createMusicalBackground(fingerConfig,oneY,sixY);
//    mb1->setTag(98);
//    mb1->setPosition(Vec2(0,0));
//    this->addChild(mb1);
//    ActionInterval* a1 = mb1->MucsicalBackgroundMove(fingerConfig);
//    a1->setTag(1);
//    mb1->runAction(a1);
//    
//    MusicalBackground *mb2 = MusicalBackground::createMusicalBackground(fingerConfig,oneY,sixY);
//    mb2->setTag(99);
//    mb2->setPosition(Vec2(fingerConfig->contentWidth,0));
//    this->addChild(mb2);
//    ActionInterval* a2 = mb1->MucsicalBackgroundMove(fingerConfig);
//    a2->setTag(1);
//    mb2->runAction(a2);
}

void FingerRunLayer::endAnimationSetting(){
    currentMusical = 1;
}



void FingerRunLayer::musicalMove(float at){
   
    ValueVector musicals = fingerConfig->musicInfo->getMusical();
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
                auto musicalSprite = Musical::createMusical(key,value,y);
                musicalSprite->setScale(0.5);
                musicalSprite->setPosition(Vec2(fingerConfig->contentWidth,y));
                musicalSprite->setTag(currentMusical+1);
                musicalSprite->setAnchorPoint(Vec2(0,0.5));
                musicalSprite->beat = currentMusical;
                ActionInterval *ai=musicalSprite->musicalMove(fingerConfig);
                Sequence *sequence = Sequence::create(ai,CallFunc::create([this,musicalSprite](){
                    musicalSprite->runLeftAction(fingerConfig);
                }),NULL);
                musicalSprite->runAction(sequence);
                
                this->addChild(musicalSprite,2);
                currMusicals.pushBack(musicalSprite);
            }
        }
 
    }
    currentMusical +=1;
}



void FingerRunLayer::stopMusic(){
    currentMusical = 0;
    delete fingerConfig;
}