//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GuitarRunScene.h"
#include "MainLayer.h"

//创建场景
Scene *GuitarRun::createScene(MusicInfo *musicInfo){
    auto scene=Scene::create();
   
    auto layer = GuitarRun::create();

    layer->startMusic(musicInfo);
    
    scene->addChild(layer);
    
    
    //设置背景
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    auto sprite = Sprite::create("background.png");
//    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
//    // add the sprite as a child to this layer
//    scene->addChild(sprite, 0);
    
    
    return scene;
}
MainLayer *mainLayer;
void GuitarRun::startMusic(MusicInfo *musicInfo){
    // 1. super init first
   
    mainLayer = MainLayer::createMainLayer(musicInfo);
    this->addChild(mainLayer,1);
}


void GuitarRun::goBack(cocos2d::Ref *sender){
    if(mainLayer){
        mainLayer->stopMusic();
    }
    Director::getInstance()->popScene();
}