//
//  EndLayer.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "POPTBaseDefine.h"

EndLayer* EndLayer::createEndLayer(){
    EndLayer *item = new EndLayer();
    if(item && item->initWithColor(Color4B(0, 0, 0, 200))){
        item->autorelease();
        item->setPosition(0,0);
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

void EndLayer::loadFrame(){

    auto endLayer = CSLoader::createNode("game/end/EndLayer.csb");
    addChild(endLayer,MASK_WIDGET_LAYER);
    
    for (int i=1; i<4; i++) {
        auto starAction = CSLoader::createTimeline("game/end/Star.csb");
        starAction->gotoFrameAndPlay(0, false);
        auto starNode = endLayer->getChildByName("star"+POPTStringUtils::intToString(i));
        starNode->runAction(starAction);
    }
    
    auto backBtn = (ui::Button*)endLayer->getChildByName("backBtn");
    backBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::backController, this));
    
    auto nextBtn = (ui::Button*)endLayer->getChildByName("nextBtn");
    nextBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::nextController, this));

    auto restartBtn = (ui::Button*)endLayer->getChildByName("restartBtn");
    restartBtn->addClickEventListener(CC_CALLBACK_1(EndLayer::restartController, this));
    
}

void EndLayer::restartController(cocos2d::Ref *ref){
    //重新闯关
    _delegate->endRestartCallback();
}

void EndLayer::backController(cocos2d::Ref *ref){
    //返回首页
    _delegate->endBackCallback();
}

void EndLayer::nextController(cocos2d::Ref *ref){
    //继续下一关
    _delegate->endNextCallback();
}

void EndLayer::setDelegate(EndLayerDelegate *delegate){
    _delegate = delegate;
}