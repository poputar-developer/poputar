//
//  FingerRunLayer.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "PlayRunLayer.h"
#include "POPTStringUtils.h"
#include "Section.h"
#include "POPTGlobal.h"

PlayRunLayer* PlayRunLayer::createPlayRunLayer(MusicModel *musicModel,float proportion){
    PlayRunLayer *layer = new PlayRunLayer();
    if(layer && layer->init4Finger(Color4B(0,0,0,0),musicModel,proportion))
    {
        layer->autorelease();
        return layer;
    }
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool PlayRunLayer::init4Finger(const cocos2d::Color4B &&color, MusicModel *musicModel,float proportion){
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    playConfig = new PlayConfig(visibleSize.width, visibleSize.height*proportion, musicModel);
    gameConfig = playConfig;
    poptGlobal->gni->setConfig(playConfig);
    
    bool result =  init(color);
    
    //当前音符
    currentMusical=0;
    //组装界面
    this->loadFrame();
    
    flag = 1;
    
    startMusical(0);

    //正式层
    sectionLayer = Layer::create();
    sectionLayer->setAnchorPoint(Vec2::ZERO);
    sectionLayer->setPosition(Vec2(playConfig->contentWidth,0));
    map<int,SectionInfo*> sections = playConfig->musicModel->getSections();
    int size =  (int)sections.size();
    for (int i=1; i<size+1; i++) {
        map<int,SectionInfo*> sections = playConfig->musicModel->getSections();
        Section* section = Section::createSection(sections[i],i,SECTION_FORMAL);
        sectionLayer->addChild(section);
        sectionSprite.insert(i, section);

    }
    this->addChild(sectionLayer,2);
    

    //试听层
    testSectionLayer = Layer::create();
    testSectionLayer->setAnchorPoint(Vec2::ZERO);
    testSectionLayer->setPosition(Vec2(playConfig->contentWidth,0));
    for (int i=1; i<size+1; i++) {
        map<int,SectionInfo*> sections = playConfig->musicModel->getSections();
        Section* section = Section::createSection(sections[i],i,SECTION_FORMAL);
        testSectionLayer->addChild(section);
        sectionSprite.insert(i, section);
    }
    this->addChild(testSectionLayer,0);
    
    return result;
}

void PlayRunLayer::loadFrame(){
    
    //节奏线碰撞时的动画效果
    auto animation = Animation::create();
    animation->addSpriteFrameWithFile("game/finger/finger_rhythm_2.png");
    animation->setDelayPerUnit(0.3f);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "rhythm_blink");

    ui::Scale9Sprite *mString = ui::Scale9Sprite::create("game/finger/finger_string.png");
    mString->setPreferredSize(Size(Vec2(playConfig->contentWidth, mString->getContentSize().height)));
    mString->setPosition(Vec2(playConfig->contentWidth/2,playConfig->unitHeight*7));
    this->addChild(mString,1);
    
    int stringCount = 6;
    for (int i=0; i<6; i++) {
        float stringHeight = playConfig->unitHeight*stringCount;
        stringMap[i+1]=Value(stringHeight);
        
        ui::Scale9Sprite *mString = ui::Scale9Sprite::create("game/finger/finger_string.png");
        mString->setPreferredSize(Size(Vec2(playConfig->contentWidth, mString->getContentSize().height)));
        mString->setPosition(Vec2(playConfig->contentWidth/2,stringHeight));
        this->addChild(mString,1);
        
        auto mRhythm = Sprite::create("game/finger/finger_rhythm_1.png");
        mRhythm->setPosition(Vec2(playConfig->impactLine, stringHeight));
        mRhythm->setTag(8000+i+1);
        this->addChild(mRhythm,3);
        rhythms.pushBack(mRhythm);
        
        stringCount-=1;
    }
}



void PlayRunLayer::restart(int musicalIndex){

}

void PlayRunLayer::startMusical(int musicalIndex){

}

int currentSection=-1;
int blueToothSection = -1;


void PlayRunLayer::update(float at){
    //当前音乐层距离撞线的位置
    sectionNotice(PLAYTYPE);
    sectionNotice(BLUETOOTHTYPE);
}


void PlayRunLayer::sectionNotice(int type){
    float distance=0;
    if(isAudition){
        distance = testSectionLayer->getPositionX()-playConfig->impactLine;
    }else{
        distance = sectionLayer->getPositionX()-playConfig->impactLine;
    }
    
    if(type==BLUETOOTHTYPE){ //蓝牙发送提前一个音符的位置
        distance-=playConfig->unitWidth;
    }
    int currFlag=-1;
    float currFlagTemp = (distance*-1)/playConfig->sectionWidth;
    
    float relativePosX ;
    if(currFlagTemp>=0){
        currFlag = (int)currFlagTemp;
        
        relativePosX = distance*-1 - playConfig->sectionWidth*(float)(currFlag);
        
        if (type==PLAYTYPE) {
            if(currFlag>=0 && currFlag !=currentSection){
                currentSection = currFlag;
            }
            Section* section =  sectionSprite.at(currentSection+1);
            if(section!=NULL){
                section->updateState(relativePosX,PLAYTYPE);
            }
        }else if(type==BLUETOOTHTYPE){
            if(currFlag>=0 && currFlag !=blueToothSection){
                blueToothSection = currFlag;
            }
            
            Section* section =  sectionSprite.at(blueToothSection+1);
            if(section!=NULL){
                section->updateState(relativePosX,BLUETOOTHTYPE);
            }
        }
    }
}


void PlayRunLayer::endAnimationSetting(){
    sendDataToBluetooth();
    currentMusical = 1;
    //开始移动正式音符界面
    auto beginMove = getMoveActionIterval();
    sectionLayer->runAction(beginMove);
}


//试听功能
void PlayRunLayer::audition(bool isAudition){
    this->isAudition = isAudition;
    //试听
    if(isAudition){
        testSectionLayer->setPositionX(sectionLayer->getPositionX());
        sectionLayer->pause(); //暂停正式音符界面
    }else{
        auditionControll(AUDITION_STOP);
        sectionLayer->resume();  //恢复正式音符界面移动
    }
}

//移动动作
ActionInterval* PlayRunLayer::getMoveActionIterval(){
    MusicModel* musicModel =  poptGlobal->gni->getMusicModel();
    map<int,SectionInfo*> sections = musicModel->getSections();
    
    //小节总宽度
    float sectionWidth = playConfig->sectionWidth;
    int size =  (int)sections.size();
    
    int moveCount = (int)playConfig->contentWidth/(int)sectionWidth;
    if((int)playConfig->contentWidth%(int)sectionWidth >0){
        moveCount+=1;
    }
    moveCount+=size;
    
    //从开始到撞击线的距离
    float distance = playConfig->rhythmWidth;
    //因第一个和弦到撞击需要走一个距离所以初始化为1
    int count = 1;
    //计算和弦总宽度到据撞击线位置的距离
    count += (int)(size*sectionWidth)/(int)distance;
    //如果有超出则会+1
    if((int)(moveCount*sectionWidth)%(int)distance>0){
        count+=1;
    }
    //移动时间
    float time = playConfig->allTime*count;
    MoveBy *beginMove = MoveBy::create(time, Vec2(-distance*count,0));
    return beginMove;
}

//试听控制
void PlayRunLayer::auditionControll(int type){
    switch (type) {
        case AUDITION_PLAY:
            testSectionLayer->runAction(getMoveActionIterval()); //移动试听音符界面
            break;
        case AUDITION_STOP:
            testSectionLayer->stopAllActions();  //停止试听移动
            break;
        case AUDITION_PAUSE:
            testSectionLayer->pause();
            break;
        case AUDITION_RESUME:
            testSectionLayer->resume();
            break;
        default:
            break;
    }
}

void PlayRunLayer::stopMusic(){
    currentMusical = 0;
    flag = 0;
    delete playConfig;
}

void PlayRunLayer::sendDataToBluetooth(){
    
}

float PlayRunLayer::getMusicalTime(int musicalIndex){
    return musicalIndex * playConfig->unitTime;;
}

string PlayRunLayer::getMusicalChord(int musicalIndex){
    return "";
}


void PlayRunLayer::sectionPause(){
    sectionLayer->pause();
};

void PlayRunLayer::sectionResume(){
    sectionLayer->resume();
};


void PlayRunLayer::auditionSilderPos(Ref* ref){
    testSectionLayer->stopAllActions();
    //1.获得试听时间轴拖动的位置
    auto value = (__Float*)ref;
    
    
    float currentX = value->getValue() * playConfig->move4sec;
    
    float auditionX = playConfig->contentWidth-currentX;
    
    testSectionLayer->setPositionX(auditionX);
    auditionControll(AUDITION_PLAY);
//    auto beginMove = getMoveActionIterval();
//    testSectionLayer->runAction(beginMove);
    
    log("test X:%f",auditionX);
    //2.根据时间轴计算当前试听的拍数
    //3.定位试听层到拍数所在位置
    
    
    
    
}