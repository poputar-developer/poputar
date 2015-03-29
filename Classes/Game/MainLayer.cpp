//
//  MainLayer.cpp
//  Guitars
//
//  Created by allen on 14-12-23.
//
//

#include "MainLayer.h"
#include "MusicAnalysis.h"
#include "POPTHelper.h"
int currentBeat;

Vector<Chord*> currBeatChords;
Vector<Chord*> waitBeatChords;

int nextBlueIndex = 0;

//当前弹奏和弦(碰撞时刻的下一个和弦）
Sprite* currCollision;


MainLayer* MainLayer::createMainLayer(MusicInfo *musicInfo){
    MainLayer *layer = new MainLayer();
    if(layer && layer->init(Color4B(0,0,0,0),musicInfo))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool MainLayer::init(const cocos2d::Color4B &&color,MusicInfo *musicInfo){
    bool result =  initWithColor(color);
    
    common = Common::getInstance(visibleSize.width, visibleSize.height*0.7, musicInfo);
    //==============设置内容页大小==============
//    //设置大小
    this->setContentSize(CCSizeMake(visibleSize.width, common->contentHeight));
//    //设置锚点
    this->setAnchorPoint(CCPoint::ZERO);
    float sideHeight = (visibleSize.height-common->contentHeight)/2;
//    //设置位置
    this->setPosition(Point(0,sideHeight));
//    //当前小节
    currentBeat=0;
//    //初始化第一小节的和弦
    this->getNewChords();
//    this->getLyric();
//
    this->getNewRhythm(true);
    this->startAnimation();
    schedule(schedule_selector(MainLayer::rhythmMove), common->rhythm_time, kRepeatForever, common->startTime);
//
    scheduleUpdate();
    return result;
}

//开始动画方法
void MainLayer::startAnimation(){
    int visibleWidth = visibleSize.width;
    //倒计时动画
    SpriteFrame *startSpriteFrame = SpriteFrame::create("1.png", Rect(0,0,100,100));

    Sprite *startSprite = Sprite::createWithSpriteFrame(startSpriteFrame);
    
    startSprite->setPosition(visibleWidth/2,common->contentHeight/2);
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
        currentBeat = 1;
        this->removeChild(startSprite);
    }), NULL);
    startSprite->runAction(startSq);
//    startSprite->runAction(action);
    
}


void MainLayer::update(float dt){
    //当前小节的节奏线
    Rhythm *rhythm = (Rhythm *)this->getChildByTag(currentBeat);
    //循环当前和弦，查看是否发生碰撞
    for (auto &e:currBeatChords) {
        if(!e->isCollision && rhythm->isReal && rhythm->boundingBox().intersectsRect(e->boundingBox())){
            if(currCollision == NULL || e!=currCollision){
                currCollision = e;
                e->collisionAction(common);
                e->isCollision = true;
                this->sendDataToBluetooth();
            }
        }
    }
}

bool isFirst = true;
void MainLayer::rhythmMove(float dt){
    if(currentBeat){
        this->moveChords();
        this->getNewChords();
        currentBeat+=1;
    }
    this->getNewRhythm(false);
    
    if(isFirst){
        sendDataToBluetooth();
        isFirst = false;
    }
    
}

void MainLayer::moveChords(){
    //当前弹奏的和弦移动到屏幕外
    for (auto &e:currBeatChords) {
        ActionInterval *ai =  e->moveOut(common);
        Sequence *removeSq=Sequence::create(ai,CallFunc::create([this,e](){
                this->removeChild(e);
        }),NULL);
        e->runAction(removeSq);
    }
    currBeatChords.clear();
    //等待弹奏的和弦移动到弹奏行
    for(auto &e : waitBeatChords){
        ActionInterval *ai = e->moveToCurrent(common);
        e->runAction(ai);
        currBeatChords.pushBack(e);
    }
    waitBeatChords.clear();
}

void MainLayer::sendDataToBluetooth(){
    
    long c = POPTHelper::getCurrentTime();
    log("发送时间：%d",c);
    vector<string> bluetoothChord = common->musicInfo->getBluetoothChord();
    if(!(nextBlueIndex >= bluetoothChord.size())){
        string nextBlueType = bluetoothChord.at(nextBlueIndex);
        log("send BlueTooth : %s",nextBlueType.c_str());
        MusicAnalysis::getInstance()->sendChordStr(nextBlueType);
    }
    long c1 = POPTHelper::getCurrentTime();
    log("结束时间：%d",c1);

    
    nextBlueIndex++;
}




void MainLayer::getNewChords(){
    //初始化和弦，并从Y轴的0移动的array4Y的第一个位置
    ValueVector beatChords = common->musicInfo->getChords();
    int beatCount = common->musicInfo->getBeat();
     ValueVector lyrics = common->musicInfo->getLyircs();
    if(currentBeat<beatChords.size()){
        ValueVector lyricVector;
        if(currentBeat<lyrics.size()){
             lyricVector = lyrics.at(currentBeat).asValueVector();
            
        }
        
        ValueVector beatVector=beatChords.at(currentBeat).asValueVector();
        for (int j=0; j<beatCount; j++) {
            string type = beatVector.at(j).asString();
            
            string lyric_str;
            if(lyricVector.size()>0){
                lyric_str = lyricVector.at(j).asString();
            }
            Chord *chord = Chord::createChord(common, j, type,lyric_str);
            this->addChild(chord,2);
            waitBeatChords.pushBack(chord);
        }
        
    }else{
        currentBeat = 999;
    }
}



void MainLayer::getNewRhythm(bool first){
    //创建信息节奏线
    Rhythm *rhythmLine = Rhythm::createRhythm(common, currentBeat);
    this->addChild(rhythmLine,1);
    ActionInterval *ai;
    if(first){
        ai = rhythmLine->firstMoveRhythm(common);
    }else{
        ai = rhythmLine->moveRhythm(common);
    }
    rhythmLine->isReal = !first;
    
    Sequence *sequence = Sequence::create(ai,CallFunc::create([this,rhythmLine](){
        ActionInterval *leftAi =rhythmLine->leftMoveRhythm(common);
        Sequence *removeSq=Sequence::create(leftAi,CallFunc::create([this](){
            this->removeChildByTag(currentBeat>2 ? currentBeat-2 : 0);
        }), NULL);
        rhythmLine->runAction(removeSq);
    }),NULL);
    rhythmLine->runAction(sequence);
}

void MainLayer::stopMusic(){
    unschedule(schedule_selector(MainLayer::rhythmMove));
    unscheduleUpdate();
    this->removeAllChildren();
    
    currBeatChords.clear();
    waitBeatChords.clear();

    nextBlueIndex = 0;
}

void MainLayer::sendChordInfo(ValueVector vv){
    
}


