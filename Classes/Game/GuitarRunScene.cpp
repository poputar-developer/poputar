//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GuitarRunScene.h"
#include "ChordRunLayer.h"
#include "FingerRunLayer.h"

//创建场景
Scene *GuitarRun::createScene(MusicInfo *musicInfo,GameInfo *gameInfo){
    auto scene=Scene::create();
    auto layer = GuitarRun::create();
    string type = gameInfo->getType();
    if(type == "C"){
       layer->startChordMusic(musicInfo);
    }else if(type=="F"){
        layer->startFingerMusic(musicInfo);
    }
    scene->addChild(layer);
    
    return scene;
}
ChordRunLayer *chordRunLayer;
void GuitarRun::startChordMusic(MusicInfo *musicInfo){
    // 1. super init first
    chordRunLayer = ChordRunLayer::createChordRunLayer(musicInfo);
    this->addChild(chordRunLayer,1);
}

FingerRunLayer *fingerRunLayer;
void GuitarRun::startFingerMusic(MusicInfo *musicInfo){
    fingerRunLayer = FingerRunLayer::createFingerRunLayer(musicInfo);
    this->addChild(fingerRunLayer);
}

void GuitarRun::goBack(cocos2d::Ref *sender){
    if(chordRunLayer){
        chordRunLayer->stopMusic();
    }
    if(fingerRunLayer){
        fingerRunLayer->stopMusic();
    }
    chordRunLayer = nullptr;
    fingerRunLayer = nullptr;
    Director::getInstance()->popScene();
}