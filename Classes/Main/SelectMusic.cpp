//
//  SelectMusic.cpp
//  Guitars
//
//  Created by allen on 15-1-26.
//
//

#include "SelectMusic.h"
#include "GameLevel.h"

#include "MusicAnalysis.h"

#include "PluginHelper.h"


Scene* SelectMusic::createScene()
{
    auto scene = Scene::create();
    //Node *rootNode = CSLoader::createNode("res/MainScene.csb");
    
    auto layer = SelectMusic::create();
    scene->addChild(layer);
    return scene;
}

bool SelectMusic::init(){
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = Sprite::create("background.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
    
    
    float distance = 120;
    auto logo = Sprite::create("main_logo.png");
//    logo->setAnchorPoint(Vec2(0,0));
    logo->setPosition(Vec2(visibleSize.width/2, visibleSize.height-distance+50));
    
    this->addChild(logo,2);
    auto sprite_sp = Sprite::create("bj_suspend.png");
    sprite_sp->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    this->addChild(sprite_sp,1);
    
    ui::Button *rightbtn = ui::Button::create("right_btn.png");
    rightbtn->setAnchorPoint(Vec2::ZERO);
    Rect rect = rightbtn->getBoundingBox();
    rightbtn->setPosition(Vec2(visibleSize.width/2+20, visibleSize.height-distance));
    

    this->addChild(rightbtn,3);
    
    rightbtn->addClickEventListener(CC_CALLBACK_1(SelectMusic::toFingering, this));
    
    

    
    ui::Button *leftbtn = ui::Button::create("left_btn.png");
    leftbtn->setAnchorPoint(Vec2::ZERO);
    Rect rect4left = leftbtn->getBoundingBox();
    leftbtn->setPosition(Vec2(visibleSize.width/2-rect4left.size.width-20, visibleSize.height-distance));
    
    this->addChild(leftbtn,3);
    
    //leftbtn->addClickEventListener(CC_CALLBACK_1(SelectMusic::toFingering, this));

    
    return true;
}

void SelectMusic::toFingering(Ref* sender){
    Scene *fingeringScene = GameLevel::createScene();
    auto transition = TransitionCrossFade::create(0.5f, fingeringScene);
    Director::getInstance()->pushScene(transition);

}


