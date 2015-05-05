//
//  Section.cpp
//  poputar
//
//  Created by allen on 15-4-28.
//
//

#include "Section.h"
#include "POPTStringUtils.h"
#include "PlayChord.h"
#include "POPTGlobal.h"

//和弦播放控制标识
int chordPlayKeyFlag=-1;
//和弦发送蓝牙控制标识
int chordSendBTKeyFlag = -1;
//主音控制标识
int tonicPlayKeyFlag=-1;

Section* Section::createSection(SectionInfo* sectionInfo,int index,int type){
    Section *item = new Section();
    if(item && item->init()){
    
        PlayConfig* playConfig = (PlayConfig*)poptGlobal->gni->getConfig();
        
        //音乐信息
        MusicModel* musicModel = playConfig->musicModel;
        //小节拍数
        int beatFlag = musicModel->getBeatFlag();
        //单元宽度，拍与拍之间的距离
        float unitWidth = playConfig->unitWidth;
        //小节总宽度
        item->sectionWidth = unitWidth*beatFlag;

        float sectionX = item->sectionWidth*(float)(index-1);
        
        
        item->type = type;
        item->playConfig = playConfig;
        item->setAnchorPoint(Vec2::ZERO);
        item->setPosition(Vec2(sectionX,0));
        item->loadMusical(sectionInfo);
        item->autorelease();
        
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}



void Section::loadMusical(SectionInfo* sectionInfo){

    float unitWidth = playConfig->unitWidth;
    
    //音乐信息
    MusicModel* musicModel = playConfig->musicModel;
    //小节拍数
    int beatFlag = musicModel->getBeatFlag();
    
    //增加节奏线信息
    for(int i=0;i<beatFlag*2;i++){
        float x = unitWidth * i/2;
        ui::Scale9Sprite *fingerRhythem = ui::Scale9Sprite::create("game/finger/finger_rhythm.png");
        fingerRhythem->setAnchorPoint(Vec2(0.5,0));
        fingerRhythem->setPosition(x,playConfig->unitHeight);
        fingerRhythem->setPreferredSize(Size(fingerRhythem->getContentSize().width,playConfig->unitHeight*5));
        if(type == SECTION_FORMAL){
            this->addChild(fingerRhythem);
        }
        
    }
    
    float minBeatWidth = unitWidth/minFlag; //最小单元长度 代表 0.25个节拍长度
    double minLength = 1.0000000f/(double)minFlag;
    
    
    //和弦信息
    vector<BeatInfo*> beats = sectionInfo->beats;
    
    int beatIndex=0;
    BeatInfo* beat;
    double bLengthFlag = 0;
    
    
    if(type == SECTION_FORMAL){
        //组装头部和弦部分
        string lastChordFlag;
        for (int b=0; b<minFlag*beatFlag; b++) {
            float bX = minBeatWidth *b      ; //当前x位置
            
            if(bLengthFlag == 0 && beatIndex<beats.size()){
                beat = beats[beatIndex];
                beatIndex++;
                bLengthFlag = beat->length;
                //新建一个和弦
                string chordType = beat->chordType;
                float chordY = playConfig->unitHeight*7;
                if(lastChordFlag.empty() || lastChordFlag != chordType){
                    //头部和弦信息
                    lastChordFlag = chordType;
                    
                    createHeadChord(chordType, Vec2(bX,chordY), Size(minBeatWidth*bLengthFlag/minLength, unitWidth));
                    //和弦切换 如果第一个和弦和上一个小节最后一个
                    if(b!=0 || lastSection.empty() || lastSection != chordType){
                        //头部和弦标识信息
                        Label *l = Label::createWithTTF(chordType, "fonts/yuanti.ttf", 20);
                        l->setColor(Color3B(0,0,0));
                        l->setAnchorPoint(Vec2::ZERO);
                        l->setPosition(Vec2(bX+5,chordY));
                        this->addChild(l);
                    }
                    
                }else{
                    if(type == SECTION_FORMAL){
                        createHeadChord(chordType, Vec2(bX,chordY), Size(minBeatWidth*bLengthFlag/minLength, unitWidth));
                    }
                }
            }
            bLengthFlag -= minLength;
        }
    }
    
    //和弦弹奏部分
    beatIndex=0;
    bLengthFlag = 0;
    
    for (int b=0; b<minFlag*beatFlag; b++) {
        
        float bX = minBeatWidth *b      ; //当前x位置
        
        if(bLengthFlag == 0 && beatIndex<beats.size()){
            beat = beats[beatIndex];
            beatIndex++;
            bLengthFlag = beat->length;
            //新建一个和弦
            if(!beat->play.empty() && beat->play!=""){
                //新建一个和弦
                PlayChord* chord = PlayChord::createPlayChord(beat, "lvse.png", bX);
                if(type==SECTION_FORMAL){
                    this->addChild(chord);
                }
                playChords.insert(b, chord);
            }
        }
        bLengthFlag -= minLength;
    }
    
    

    //主音信息
    map<int,TonicInfo*> tonics = sectionInfo->tonics;
    int tonicIndex=0;
    double tLengthFlag = 0;
    TonicInfo *tonic;
  
    for (int t=0; t<minFlag*beatFlag; t++) {
        if(tLengthFlag == 0 && tonicIndex<tonics.size()){
            tonic = tonics.at(tonicIndex+1);
            tonicIndex++;
            tLengthFlag = tonic->length;
            if(!tonic->note.empty() && tonic->note!=""){
                __String *note = __String::create(tonic->note);
                playTonics.insert(t, note);
            }
        }
        tLengthFlag -= minLength;
    }

}


void Section::createHeadChord(string chordType, cocos2d::Vec2 position, cocos2d::Size preferredSize){
    //根据和弦类型来取和弦类型及颜色
    string fileName ;
    if(chordType =="C"){
        fileName = "lvse.png";
    }else{
        fileName = "huangse.png";
    }
    ui::Scale9Sprite *css = ui::Scale9Sprite::create(fileName);
    css->setAnchorPoint(Vec2::ZERO);
    css->setPosition(position);
    css->setPreferredSize(preferredSize);
    this->addChild(css);
}


ActionInterval* Section::move(int sectionCount){
    int moveCount = (int)playConfig->contentWidth/(int)sectionWidth;
    if((int)playConfig->contentWidth%(int)sectionWidth >0){
        moveCount+=1;
    }
    moveCount+=sectionCount;
    float time = playConfig->allTime*moveCount;
    float distance = playConfig->rhythmWidth;
    MoveBy *beginMove = MoveBy::create(time, Vec2(-distance*moveCount,0));
    return beginMove;
}



void Section::updateState(float relativePosX,int nType){
    
    PlayConfig* playConfig = (PlayConfig*)poptGlobal->gni->getConfig();
    float unitWidth = playConfig->unitWidth;
    float minBeatWidth = unitWidth/minFlag;
    int key = relativePosX/minBeatWidth;
    if(nType == PLAYTYPE){
        if(key!=chordPlayKeyFlag){  //切换播放和弦
            if(playChords.find(key) != playChords.end()){
                PlayChord* pc = playChords.at(key);
                string type = pc->beatInfo->chordType;
                //播放声音
                string chordFileName = "audio/chord/"+type+"_clean.caf";
                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(chordFileName.c_str(),false,1,0,1);
                //通知右手区
                sendBlueTooth4Beat(pc);
                
            }
            chordPlayKeyFlag = key;
        }
    }else if(nType == BLUETOOTHTYPE){
        if(key != chordSendBTKeyFlag){ //切换蓝牙发送和弦
            if(playChords.find(key) != playChords.end()){
                PlayChord* pc = playChords.at(key);
                string type = pc->beatInfo->chordType;
                sendBlueTooth4Chord(pc);
            }
            chordSendBTKeyFlag = key;
        }
    }
    
    if(nType==PLAYTYPE){
        if(key!=tonicPlayKeyFlag){
            
            if(playTonics.find(key)!=playTonics.end()){
                __String *note = playTonics.at(key);
                
                string note4Str = note->getCString();
                float upOrDown = 1.00f;
                if(!note4Str.empty() && note4Str !="0" ){
                    string scaleFileName ="audio/scale/"+note4Str+".mp3";
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(scaleFileName.c_str(),false,upOrDown,0,1);
                }
                
//                log("%d",(int)index);
            }
            tonicPlayKeyFlag = key;
        }
    }
}

void Section::sendBlueTooth4Chord(PlayChord *chord){
    string type = chord->beatInfo->chordType;
    log("send blueTooth chord data %s",type.c_str());
}

void Section::sendBlueTooth4Beat(PlayChord *chord){
    
}

