//
//  EndLayer.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "../../Base/POPTBaseDefine.h"

EndLayer* EndLayer::createEndLayer(bool gameResult,bool isPassLevel){
    EndLayer *item = new EndLayer();
    if(item && item->initWithColor(Color4B(0, 0, 0, 200))){
        item->autorelease();
        item->setPosition(0,0);
        item->loadFrame(gameResult);
        item->isPassLevel = isPassLevel;
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

void EndLayer::loadFrame(bool gameReslut){

    auto endLayer = CSLoader::createNode("game/end/EndLayer.csb");
    addChild(endLayer,MASK_WIDGET_LAYER);
    
    for (int i=1; i<4; i++) {
        auto startAction = CSLoader::createTimeline("game/end/Star.csb");
        startAction->gotoFrameAndPlay(0, false);
        auto starNode = endLayer->getChildByName("star"+POPTStringUtils::intToString(i));
        starNode->runAction(startAction);
    }
    
    auto restartBtn = (ui::Button*)endLayer->getChildByName("restartBtn");
    restartBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::restartController, this));
    
    auto backBtn = (ui::Button*)endLayer->getChildByName("backBtn");
    backBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::backController, this));
    
    auto nextBtn = (ui::Button*)endLayer->getChildByName("nextBtn");
    nextBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::nextController, this));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    if (!gameReslut) {
        backBtn->setPosition(Vec2(visibleSize.width/2-150,restartBtn->getPositionY()));
        restartBtn->setPosition(Vec2(visibleSize.width/2+150,restartBtn->getPositionY()));
        nextBtn->setVisible(false);
    }
}

void EndLayer::restartController(cocos2d::Ref *ref){
    //重新闯关
    _delegate->endRestartCallback();
}

void EndLayer::backController(cocos2d::Ref *ref){
    //返回首页
    _delegate->endBackCallback(isPassLevel);
}

void EndLayer::nextController(cocos2d::Ref *ref){
    //继续下一关
    _delegate->endNextCallback(isPassLevel);
}

void EndLayer::setDelegate(EndLayerDelegate *delegate){
    _delegate = delegate;
}