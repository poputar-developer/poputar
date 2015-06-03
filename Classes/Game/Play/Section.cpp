//
//  Section.cpp
//  poputar
//
//  Created by allen on 15-4-28.
//
//

#include "../../Base/POPTBaseDefine.h"
#include <stdlib.h>
//和弦播放控制标识
int chordPlayKeyFlag=-1;
//和弦发送蓝牙控制标识
int chordSendBTKeyFlag = -1;
//主音控制标识
int tonicPlayKeyFlag=-1;
//节拍器控制
int metronomeKeyFlag=-1;

Section* Section::createSection(SectionInfo* sectionInfo,int index,int type,int p_index,int s_index){
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
        item->p_index = p_index;
        item->s_index = s_index;
        
        item->sectionIndex = index;
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


void Section::loadRhythm(){
    float unitWidth = playConfig->unitWidth;
    //音乐信息
    MusicModel* musicModel = playConfig->musicModel;
    //小节拍数
    int beatFlag = musicModel->getBeatFlag();
    
    //增加节奏线信息
    for(int i=0;i<beatFlag*2;i++){
        float x = unitWidth * i/2;
        ui::Scale9Sprite *fingerRhythem = ui::Scale9Sprite::create("game/play/rhythm.png");
        fingerRhythem->setAnchorPoint(Vec2(0.5,0));
        fingerRhythem->setPosition(x,playConfig->stringSideHeight);
        if(i==0){
            fingerRhythem->setPreferredSize(Size(fingerRhythem->getContentSize().width,playConfig->contentHeight-playConfig->stringSideHeight));
        }else{
            fingerRhythem->setPreferredSize(Size(fingerRhythem->getContentSize().width,playConfig->stringsHeight));
        }
        
        this->addChild(fingerRhythem);
        
    }
}



void Section::loadMusical(SectionInfo* sectionInfo){
    
    //和弦声音控制
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Section::chordVoiceCallback), POPT_CHORD_VOICE , NULL);
    //主音声音控制
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Section::toincVoiceCallBack), POPT_TOINC_VOICE , NULL);
    //节拍器声音控制
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Section::metronomeVoiceCallback), POPT_METRONOME_VOICE , NULL);
    //音调控制（品夹）
    __NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Section::capoChangeCallback), POPT_CAPO_VALUE , NULL);
    
    
    //默认和弦声音关闭，主音开放，节拍器关闭
    chordVoice = false;
    toincVoice = false;
    metronomeVoice = false;
    capoValue = 1.0f;
    
    float unitWidth = playConfig->unitWidth;

    //音乐信息
    MusicModel* musicModel = playConfig->musicModel;
    //小节拍数
    int beatFlag = musicModel->getBeatFlag();
    
    //正常部分和展示部分
    if(type==SECTION_FORMAL_CHORD || type == SECTION_FORMAL_TONIC ||type==SECTION_SHOW){
        loadRhythm();
    }
    float minBeatWidth = unitWidth/minFlag; //最小单元长度 代表 0.25个节拍长度
    double minLength = 1.0000000f/(double)minFlag;
    int beatIndex=0;
    BeatInfo* beat;
    double bLengthFlag = 0;
    
    //正常部分
    if(type == SECTION_FORMAL_CHORD){
        //和弦信息
        map<int,BeatInfo*> beats = sectionInfo->beats;
        //组装头部和弦部分
        string lastChordFlag;
        for (int b=0; b<minFlag*beatFlag; b++) {
            float bX = minBeatWidth *b      ; //当前x位置
            
            if(bLengthFlag == 0 && beatIndex<beats.size()){
                beat = beats.at(beatIndex+1);//[beatIndex];
                beatIndex++;
                bLengthFlag = beat->length;
                //新建一个和弦
                string chordType = beat->chordType;
                if(chordType=="" && chordType.empty()){
                    continue;
                }
                float chordY = playConfig->contentHeight-playConfig->chordHeight;
                
                if(lastChordFlag.empty() || lastChordFlag != chordType){
                    //头部和弦信息
                    lastChordFlag = chordType;
                    
                    //创建和弦色块
                    //createHeadChord(chordType, Vec2(bX,chordY), Size(minBeatWidth*bLengthFlag/minLength, playConfig->chordHeight));
                    //和弦切换 如果第一个和弦和上一个小节最后一个
                    if(b!=0 || lastSection.empty() || lastSection != chordType){
                        
                        //头部和弦标识信息
                        Label *l = Label::createWithTTF(chordType, "fonts/STHeiti-Light.ttc", 50);
                        l->setColor(getChordColor(chordType));
                        l->setAnchorPoint(Vec2(0,0.5));
                        l->setPosition(Vec2(bX+20,chordY+playConfig->chordHeight/2));
                        this->addChild(l);
                        

                        auto chordPic = Sprite::create("game/play/"+getChordFlag(chordType)+"_chord.png");
                        chordPic->setAnchorPoint(Vec2(0,0.5));
                        chordPic->setPosition(Vec2(l->getPositionX()+l->getContentSize().width+20,chordY+playConfig->chordHeight/2));
                        this->addChild(chordPic);
                        
                        //log("label：%f --- pic：%f",bX+20,l->getPositionX()+l->getContentSize().width+20);
                    }
                    
                }else{
                    //createHeadChord(chordType, Vec2(bX,chordY), Size(minBeatWidth*bLengthFlag/minLength, playConfig->chordHeight));
                }
            }
            bLengthFlag -= minLength;
        }
    }
    
    //正常部分和试听部分
    if(type == SECTION_FORMAL_CHORD || type == SECTION_FORMAL_TONIC || type == SECTION_AUDITION){
        //和弦信息
        map<int,BeatInfo*> beats = sectionInfo->beats;
        //和弦弹奏部分
        beatIndex=0;
        bLengthFlag = 0;
        
        for (int b=0; b<minFlag*beatFlag; b++) {
            
            float bX = minBeatWidth *b; //当前x位置
            
            if(bLengthFlag == 0 && beatIndex<beats.size()){
                beat = beats.at(beatIndex+1);
                beatIndex++;
                bLengthFlag = beat->length;
                string chordFlag;
                //新增弹奏方式
                if(!beat->play.empty() && beat->play!=""){
                    
                    string chordType = beat->chordType;
                    chordFlag = getChordFlag(chordType);
                    string lineFileName = "game/play/"+chordFlag+"_line.png";
                    string circleFileName = "game/play/"+chordFlag+"_circle.png";
                    
                    //新建一个扫弦区域
                    PlayChord* chord = PlayChord::createPlayChord(beat, lineFileName,circleFileName, bX);
                    if(type==SECTION_FORMAL_CHORD){
                        this->addChild(chord);
                    }
                    playChords.insert(b, chord);
                }
                
                //增加特殊弹奏标识
                if(!beat->stringInfo.empty() && beat->stringInfo!=""){
//                    if(chordFlag.empty() && chordFlag == ""){
//                        if(sectionIndex%2 == 0){
//                            chordFlag="C";
//                        }else{
//                            chordFlag="Am";
//                        }
//                    }
                    string circleFileName = "game/play/"+chordFlag+"_circle.png";
                    vector<string> strings = POPTStringUtils::split(beat->stringInfo, "@|@");
                    for (int i=0; i<strings.size(); i++) {
                        vector<string> strVec = POPTStringUtils::split(strings[i], ":");
                        string strInfo = strVec[0];
                        string cop = strVec[1];
                        auto playStr = PlayString::createPlayString(strInfo,cop,circleFileName,bX);
                        if(type==SECTION_FORMAL_CHORD){
                            this->addChild(playStr);
                        }
                        
                    }
                }
            }
            bLengthFlag -= minLength;
        }
        
        //主音信息
        map<int,TonicInfo*> tonics = sectionInfo->tonics;
        int tonicIndex=0;
        double tLengthFlag = 0;
        TonicInfo *tonic;
        
        string fileTemp = POPTStringUtils::intToString((rand()%7)+1);
        
        for (int t=0; t<minFlag*beatFlag; t++) {
            float tX = minBeatWidth *t;
            if(tLengthFlag == 0 && tonicIndex<tonics.size()){
                tonic = tonics.at(tonicIndex+1);
                tonicIndex++;
                tLengthFlag = tonic->length;
                if(!tonic->note.empty() && tonic->note!="" && tonic->note!="0"){
                    __String *note = __String::create(tonic->note);
                    playTonics[t]=tonic;
                    if(type==SECTION_FORMAL_TONIC){
                        //得到弦信息
                        string tonicStrInfo = tonic2StrSingleton->getStrInfo(note->getCString());
                        vector<string> strVec = POPTStringUtils::split(tonicStrInfo, ":");
                        string strInfo = strVec[0];
                        string cop = strVec[1];
                        
                        auto playStr = PlayString::createPlayString(strInfo,cop,"game/finger/"+fileTemp+"_circle.png",tX);
                        
                        this->addChild(playStr);
                    }
                }
            }
            tLengthFlag -= minLength;
        }
    }
}

string Section::getChordFlag(string chordType){
    string chordFlag = chordType.substr(0,1);
    if(chordFlag[0]>='a' && chordFlag[0]<='z'){
        
        chordFlag = POPTStringUtils::toUpper(chordFlag);
    }
    return chordFlag;
}

Color3B Section::getChordColor(string chordType){
    
    string chordFlag = getChordFlag(chordType);
    Color3B color;
    if (chordFlag=="C") {
        color=Color3B(240,209,0);
    }else if (chordFlag=="D") {
        color=Color3B(83,144,238);
    }else if (chordFlag=="E") {
        color=Color3B(240,209,0);
    }else if (chordFlag=="F") {
        color=Color3B(240,209,0);
    }else if (chordFlag=="G") {
        color=Color3B(161,201,14);
    }else if (chordFlag=="A") {
        color=Color3B(11,239,253);
    }else if (chordFlag=="B") {
        color=Color3B(240,209,0);
    }
    return color;
}


void Section::createHeadChord(string chordType, cocos2d::Vec2 position, cocos2d::Size preferredSize){
    //根据和弦类型来取和弦类型及颜色
    string fileName ;

    fileName = "game/base/chordbanner.png";
    
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



bool Section::updateState(float relativePosX,int nType){
    bool result= false;
    PlayConfig* playConfig = (PlayConfig*)poptGlobal->gni->getConfig();
    
    float unitWidth = playConfig->unitWidth;
    float minBeatWidth = unitWidth/minFlag;
    int key = relativePosX/minBeatWidth;
    
    
    
    //如果key为奇数，则是每拍的开始和中间位置，节奏线的位置
    //应该在此处节拍器 默认开
    if(metronomeVoice && (nType == UPDATE_TYPE_CHORD ||nType == UPDATE_TYPE_TONIC) && key != metronomeKeyFlag && key%minFlag == 0){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/snare.caf",false,6,0,1);
        metronomeKeyFlag = key;
    }
    
    if(nType == UPDATE_TYPE_CHORD || nType == UPDATE_TYPE_TONIC){
        if(key!=chordPlayKeyFlag){  //切换播放和弦
            if(playChords.find(key) != playChords.end()){
                PlayChord* pc = playChords.at(key);
                string type = pc->beatInfo->chordType;
                //播放声音
                string chordFileName = "audio/chord/"+type+"_clean.caf";
                if(chordVoice){
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(chordFileName.c_str(),false,capoValue,0,1);
                }

                if(nType == UPDATE_TYPE_CHORD){
                    //通知右手区
                    sendBlueTooth4ChordLift(pc);
                    result = true;
                }
            }
            chordPlayKeyFlag = key;
        }
        
        
        if(key!=tonicPlayKeyFlag){
            
            if(playTonics.find(key)!=playTonics.end()){
                TonicInfo *tonic = playTonics.at(key);
                
                string note4Str = tonic->note;
                if(!note4Str.empty() && note4Str != "" && note4Str !="0" ){
                    //通知代理歌词信息
                    _delegate->lyricCallbak(p_index, s_index, tonic->t_index);
                    
                    string scaleFileName ="audio/scale/"+note4Str+".mp3";
                    if (toincVoice) {
                        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(scaleFileName.c_str(),false,capoValue,0,1);
                    }
                    
                    if(nType == UPDATE_TYPE_TONIC){
                        //通知右手区
                        string tonicStrInfo = tonic2StrSingleton->getStrInfo(tonic->note);
                        sendBlueTooth4tonicLift(tonicStrInfo);
                        result = true;
                    }
                }
            }
            tonicPlayKeyFlag = key;
        }
    }else if(nType == UPDATE_TYPE_BLUETOOTH){
        string musicModelType =  playConfig->musicModel->getType();
        if(key != chordSendBTKeyFlag){ //切换蓝牙发送和弦
            if(musicModelType == MUSICMODEL_TYPE_CHORD){
                
                if(playChords.find(key) != playChords.end()){
                    PlayChord* pc = playChords.at(key);
                    string type = pc->beatInfo->chordType;
                    sendBlueTooth4Chord(pc);
                }
                
            }else if(musicModelType == MUSICMODEL_TYPE_TONIC){
                if(playTonics.find(key) != playTonics.end()){
                    TonicInfo *toinc = playTonics.at(key);
                    string tonicStrInfo = tonic2StrSingleton->getStrInfo(toinc->note);
                    sendBlueTooth4Tonic(tonicStrInfo);
                }
            }
            chordSendBTKeyFlag = key;
        }
    }
    
    return result;
}

void Section::chordVoiceCallback(Ref* ref){
    __Bool *b =(__Bool*)ref;
    chordVoice = b->getValue();
}

void Section::toincVoiceCallBack(Ref* ref){
    __Bool *b =(__Bool*)ref;
    toincVoice = b->getValue();
}

void Section::metronomeVoiceCallback(Ref *ref){
    __Bool *b =(__Bool*)ref;
    metronomeVoice  = b->getValue();
}

void Section::capoChangeCallback(cocos2d::Ref *ref){
    __Float* f = (__Float*) ref;
    capoValue = f->getValue();
}

void Section::sendBlueTooth4Chord(PlayChord *chord){
    string type = chord->beatInfo->chordType;
    log("send blueTooth chord data %s",type.c_str());
}

void Section::sendBlueTooth4ChordLift(PlayChord *chord){
    
}

void Section::sendBlueTooth4Tonic(string strInfo){
    
}

void Section::sendBlueTooth4tonicLift(string strInfo){
    
}

Section::~Section(){
    __NotificationCenter::getInstance()->removeObserver(this, POPT_CHORD_VOICE);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_METRONOME_VOICE);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_TOINC_VOICE);
    __NotificationCenter::getInstance()->removeObserver(this, POPT_CAPO_VALUE);
}

void Section::setDelegate(SectionDelegate *delegate){
    _delegate = delegate;
}

