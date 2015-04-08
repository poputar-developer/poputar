//
//  GameMenu.cpp
//  poputar
//
//  Created by allen on 15-4-7.
//
//

#include "GameMenu.h"


GameMenu* GameMenu::createGameMenu(){
    GameMenu *item = new GameMenu();
    if(item && item->init()){
        item->autorelease();
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

bool GameMenu::init(){
    bool result =  Layer::init();
    this->setPosition(0,0);
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameMenu::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameMenu::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameMenu::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return result;
}

void GameMenu::loadFrame(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float gameMenuHeight = 120;
    
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("menuLayerBg.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);
    float flag;
    
    //继续游戏
    ui::Button *goOnBtn = ui::Button::create("goonBtnNormal.png","goonBtnSelect.png");
    float goonBtnWidth = goOnBtn->getContentSize().width;
    goOnBtn->setPosition(Vec2(goonBtnWidth/2+40,gameMenuHeight/2));
    goOnBtn->addClickEventListener(CC_CALLBACK_1(GameMenu::goOnController, this));
    bg->addChild(goOnBtn);
    flag = goonBtnWidth+40;
    
    //重新开始
    ui::Button *restartBtn = ui::Button::create("restartBtnNormal.png","restartBtnSelect.png");
    float restartBtnWidth = restartBtn->getContentSize().width;
    restartBtn->setPosition(Vec2(flag+restartBtnWidth/2+20,gameMenuHeight/2));
    restartBtn->addClickEventListener(CC_CALLBACK_1(GameMenu::restartController, this));
    bg->addChild(restartBtn);
    flag += restartBtnWidth+20;
    
    //返回上级
    ui::Button *gobackBtn = ui::Button::create("gobackBtnNormal.png","gobackBtnSelect.png");
    float gobackWidth = gobackBtn->getContentSize().width;
    gobackBtn->setPosition(Vec2(flag+gobackWidth/2+20,gameMenuHeight/2));
    gobackBtn->addClickEventListener(CC_CALLBACK_1(GameMenu::goBackController, this));
    bg->addChild(gobackBtn);
    flag +=gobackWidth+20;

    bg->setPreferredSize(Size(flag+40,gameMenuHeight));
}

void GameMenu::goOnController(cocos2d::Ref *ref){
    _delegate->goOnCallback(ref);
}

void GameMenu::restartController(cocos2d::Ref *ref){
    _delegate->restartCallback(ref);
}

void GameMenu::goBackController(cocos2d::Ref *ref){
    _delegate->goBackCallback(ref);
}

bool GameMenu::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    log("Touch Began");
    return true;
}

void GameMenu::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    log("move");
}

void GameMenu::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    log("end");
}

void GameMenu::setDelegate(GameMenuDelegate *delegate){
    _delegate = delegate;
}
