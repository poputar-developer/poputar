//
//  Chord.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "Chord.h"
static Lyric *lyric;
Chord::~Chord(){
    this->cocos2d::Node::removeChild(lyric);
}

//图片大小固定为72像素
bool Chord::initWithFile(string type,ChordConfig *chordConfig,int index){
    bool result;
    if (type == "") {
        result =  Sprite::init();
        //默认空和弦大小为72*72 设计大小为36*36
        this->setContentSize(Size(36,36));
    }else{
        this->type = type;
        this->getFileNameWidthType(type);
        result = Sprite::initWithFile(this->imageFileName);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(this->audioFileName.data());
    }
    this->setOpacity(150);
    float x = chordConfig->array4X.at(index).asFloat();
    this->setPosition(Vec2(x,0));

    return result;
}



Chord* Chord::createChord(ChordConfig *ChordConfig, int index, string type,string lyric_str){
    Chord *chord = new Chord();
    if(chord && chord->initWithFile(type,ChordConfig,index)){
        Lyric *l = Lyric::create();
        l->setLyircStr(lyric_str);
        chord->addChild(l);
        Size p = chord->getContentSize();
        l->setPosition(Vec2(p.width/2,-11));
        lyric=l;
        chord->autorelease();
        return chord;
    }
    return nullptr;
    CC_SAFE_DELETE(chord);
}


void Chord::getFileNameWidthType(string type){
    string imageFileName;
    string audioFileName;
    if(type == "C"){
        imageFileName = "C.png";
        audioFileName = "C_clean.caf";
    }else if (type =="D"){
        imageFileName = "D.png";
        audioFileName = "D_clean.caf";
    }else if (type =="E"){
        imageFileName = "E.png";
        audioFileName = "E_clean.caf";
    }else if (type =="F"){
        imageFileName = "F.png";
        audioFileName = "F_clean.caf";
    }else if (type =="G"){
        imageFileName = "G.png";
        audioFileName = "G_clean.caf";
    }else if (type =="A"){
        imageFileName = "A.png";
        audioFileName = "A_clean.caf";
    }else if (type =="F"){
        imageFileName = "B.png";
        audioFileName = "B_clean.caf";
    }else if (type =="Am"){
        imageFileName = "Am.png";
        audioFileName = "Am_clean.caf";
    }else if (type =="Bm"){
        imageFileName = "Bm.png";
        audioFileName = "Bm_clean.caf";
    }else if (type =="Dm"){
        imageFileName = "Dm.png";
        audioFileName = "Dm_clean.caf";
    }else if (type =="Em"){
        imageFileName = "Em.png";
        audioFileName = "Em_clean.caf";
    }
    this->imageFileName="game/chord/"+imageFileName;
    this->audioFileName="audio/chord/"+audioFileName;
}
ActionInterval *Chord::moveToWait(ChordConfig *chordConfig){
    float y = chordConfig->array4Y.at(0).asFloat();
    MoveTo *chordStartMove = MoveTo::create(chordConfig->unitTime/2, Vec2(this->getPosition().x,y));
    return chordStartMove;
}


ActionInterval *Chord::moveToCurrent(ChordConfig *chordConfig){
    float y = chordConfig->array4Y.at(1).asFloat();
    MoveTo *chordSecondMove = MoveTo::create(chordConfig->unitTime/2, Vec2(this->getPosition().x,y));
    FadeIn *chordSecondFade = FadeIn::create(chordConfig->unitTime/2);
    Spawn *spawn = Spawn::create(chordSecondMove,chordSecondFade, NULL);
    return spawn;
}

ActionInterval *Chord::moveOut(ChordConfig *chordConfig){
    MoveTo *chordEndMove = MoveTo::create(chordConfig->unitTime/2, Vec2(this->getPosition().x,chordConfig->contentHeight));
    FadeOut *out = FadeOut::create(chordConfig->unitTime/2);
    Spawn *spawn = Spawn::create(chordEndMove,out, NULL);
    return spawn;
}

void Chord::collisionAction(ChordConfig *chordConfig){
    
    if (this->audioFileName.empty()) {
        return;
    }
    ActionInterval *scale = ScaleBy::create(0.25, 2);
    Sequence *sq = Sequence::create(scale,CallFunc::create([this](){
        ActionInterval *scale = ScaleBy::create(0.25, 0.5);
        this->runAction(scale);
    }), NULL);
    this->runAction(sq);
}

void Chord::chordVoice(float capoValue){
    if(this->audioFileName.empty()){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(this->audioFileName.data(),false,capoValue,0,1);

    }
}

string Chord::getType(){
    return this->type;
}


