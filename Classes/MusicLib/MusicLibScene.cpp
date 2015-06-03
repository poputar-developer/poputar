//
//  MusicLibScene.cpp
//  poputar
//
//  Created by allen on 15-6-3.
//
//


#include "POPTBaseDefine.h"

Scene* MusicLibScene::createScene(){
    auto scene = Scene::create();
    auto layer = MusicLibScene::create();
    scene->addChild(layer);
    return scene;

}

bool MusicLibScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    auto musicLibScene = CSLoader::createNode("musicLib/MusicLibScene.csb");
    this->addChild(musicLibScene);
    
    auto backBtn = (ui::Button*)musicLibScene->getChildByName("backBtn");
    backBtn->addClickEventListener(CC_CALLBACK_1(MusicLibScene::backBtnController, this));
    
    return true;
}

void MusicLibScene::backBtnController(cocos2d::Ref *ref){
    Director::getInstance()->popScene() ;
}