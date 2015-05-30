//
//  PassSence.cpp
//  poputar
//
//  Created by allen on 15-5-30.
//
//

#include "POPTBaseDefine.h"

Scene* PassSence::createScene(){
    auto scene=Scene::create();
    auto layer = PassSence::create();
    scene->addChild(layer);
    return scene;
}

bool PassSence::init(){
    bool result = Layer::init();
    if(!result){
        return result;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto passLayer = CSLoader::createNode("game/pass/PassLayer.csb");
    passLayer->setContentSize(visibleSize);
    pickNode = passLayer->getChildByName("PickNode");
    this->addChild(passLayer);
    
    int levle = UserDefault::getInstance()->getIntegerForKey(CURR_LEVEL_KEY);
    startPickAction(levle);
    
    Button* goOn =(Button*)passLayer->getChildByName("GoOn");
    goOn->addClickEventListener(CC_CALLBACK_1(PassSence::goOnController, this));
    
    return result;
}


void PassSence::goOnController(cocos2d::Ref *ref){
    Director::getInstance()->popScene();
}

void PassSence::startPickAction(int level){
    int startFrame = defaultFrame*(level-1);
    
    int endFrame = defaultFrame*level;
    
    auto startAction = CSLoader::createTimeline("game/pass/Pick.csb");
    
    startAction->gotoFrameAndPlay(startFrame, endFrame, false);
    
    pickNode->runAction(startAction);
    
}