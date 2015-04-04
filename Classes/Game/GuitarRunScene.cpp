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
    
    layer->loadFrame(musicInfo);
    
    string type = gameInfo->getType();
    //C代表和弦界面 F代表指弹界面
    if(type == "C"){
       layer->startChordMusic(musicInfo);
    }else if(type=="F"){
        layer->startFingerMusic(musicInfo);
    }
    scene->addChild(layer);
    
    return scene;
}

void GuitarRun::loadFrame(MusicInfo *musicInfo){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    string title = "歌曲："+musicInfo->getTitle();
    auto label = Label::createWithTTF(title, "fonts/manhuati.ttf", 20);
    label->setPosition( label->getContentSize().width,visibleSize.height-label->getContentSize().height);
    this->addChild(label);
    
    
}

void GuitarRun::startChordMusic(MusicInfo *musicInfo){
    runLayer = ChordRunLayer::createChordRunLayer(musicInfo);
    this->addChild(runLayer,1);
}

void GuitarRun::startFingerMusic(MusicInfo *musicInfo){
    runLayer = FingerRunLayer::createFingerRunLayer(musicInfo);
    this->addChild(runLayer);
}

void GuitarRun::goBack(cocos2d::Ref *sender){
    if(runLayer){
        runLayer->stopMusic();
    }
    runLayer = nullptr;
    Director::getInstance()->popScene();
}