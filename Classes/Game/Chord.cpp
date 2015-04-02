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

bool Chord::initWithFile(string type,ChordConfig *chordConfig,int index){
    bool result;
    if (type == "") {
        result =  Sprite::init();
    }else{
        this->type = type;
        this->getFileNameWidthType(type);
        result = Sprite::initWithFile(this->imageFilename);
        this->setOpacity(150);
        this->setScale(0.7);
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(this->voideFileName);
    }
    float x = chordConfig->array4X.at(index).asFloat();
    float y = chordConfig->array4Y.at(0).asFloat();
    this->setPosition(Vec2(x,0));
    MoveTo *chordStartMove = MoveTo::create(chordConfig->unitSpeed/2, Vec2(x,y));
    this->runAction(chordStartMove);
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
//        l->setAnchorPoint(Vec2(0,0));
        lyric=l;
        chord->autorelease();
        return chord;
    }
    return nullptr;
    CC_SAFE_DELETE(chord);
}


void Chord::getFileNameWidthType(string type){
    if(type == "C"){
        this->imageFilename = "C.png";
        this->voideFileName = "C_clean.caf";
    }else if (type =="D"){
        this->imageFilename = "D.png";
        this->voideFileName = "D_clean.caf";
    }else if (type =="E"){
        this->imageFilename = "E.png";
        this->voideFileName = "E_clean.caf";
    }else if (type =="F"){
        this->imageFilename = "F.png";
        this->voideFileName = "F_clean.caf";
    }else if (type =="G"){
        this->imageFilename = "G.png";
        this->voideFileName = "G_clean.caf";
    }else if (type =="A"){
        this->imageFilename = "A.png";
        this->voideFileName = "A_clean.caf";
    }else if (type =="F"){
        this->imageFilename = "B.png";
        this->voideFileName = "B_clean.caf";
    }else if (type =="Am"){
        this->imageFilename = "Am.png";
        this->voideFileName = "Am_clean.caf";
    }else if (type =="Bm"){
        this->imageFilename = "Bm.png";
        this->voideFileName = "Bm_clean.caf";
    }else if (type =="Dm"){
        this->imageFilename = "Dm.png";
        this->voideFileName = "Dm_clean.caf";
    }else if (type =="Em"){
        this->imageFilename = "Em.png";
        this->voideFileName = "Em_clean.caf";
    }
}

ActionInterval *Chord::moveToCurrent(ChordConfig *chordConfig){
    MoveTo *chordSecondMove = MoveTo::create(chordConfig->unitSpeed/2, Vec2(this->getPosition().x,chordConfig->array4Y.at(1).asFloat()));
    FadeIn *chordSecondFade = FadeIn::create(chordConfig->unitSpeed/2);
    Spawn *spawn = Spawn::create(chordSecondMove,chordSecondFade, NULL);
    return spawn;
}

ActionInterval *Chord::moveOut(ChordConfig *chordConfig){
    MoveTo *chordEndMove = MoveTo::create(chordConfig->unitSpeed/2, Vec2(this->getPosition().x,chordConfig->contentHeight));
    FadeOut *out = FadeOut::create(chordConfig->unitSpeed/2);
    Spawn *spawn = Spawn::create(chordEndMove,out, NULL);
    return spawn;
}

void Chord::collisionAction(ChordConfig *chordConfig){
    
    if (this->voideFileName ==NULL) {
        return;
    }
    
    ActionInterval *scale = ScaleBy::create(0.25, 2);
    Sequence *sq = Sequence::create(scale,CallFunc::create([this](){
        ActionInterval *scale = ScaleBy::create(0.25, 0.5);
        this->runAction(scale);
    }), NULL);
    this->runAction(sq);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(this->voideFileName);
}

string Chord::getType(){
    return this->type;
}


