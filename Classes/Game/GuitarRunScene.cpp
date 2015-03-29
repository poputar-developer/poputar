//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GuitarRunScene.h"
#include "ChordRunLayer.h"

//创建场景
Scene *GuitarRun::createScene(MusicInfo *musicInfo){
    auto scene=Scene::create();
   
    auto layer = GuitarRun::create();

    layer->startMusic(musicInfo);
    
    scene->addChild(layer);
    
    return scene;
}
ChordRunLayer *chordRunLayer;
void GuitarRun::startMusic(MusicInfo *musicInfo){
    // 1. super init first
    chordRunLayer = ChordRunLayer::createChordRunLayer(musicInfo);
    this->addChild(chordRunLayer,1);
}


void GuitarRun::goBack(cocos2d::Ref *sender){
    if(chordRunLayer){
        chordRunLayer->stopMusic();
    }
    Director::getInstance()->popScene();
}