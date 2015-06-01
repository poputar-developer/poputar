//
//  GameLevelCardHandler.cpp
//  poputar
//
//  Created by allen on 15-5-9.
//
//

#include "../Base/POPTBaseDefine.h"


USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;

GameLevelCardHandler::GameLevelCardHandler(){
};

Widget::ccWidgetTouchCallback GameLevelCardHandler::onLocateTouchCallback(const string &callBackName)
{
    if (callBackName == "onTouch")//判断事件名，返回对应的函数。下同
    {
        return CC_CALLBACK_2(GameLevelCardHandler::onTouch, this);
    }
    return nullptr;
}
Widget::ccWidgetClickCallback GameLevelCardHandler::onLocateClickCallback(const string &callBackName)
{
    if (callBackName == "onClick")
    {
        return CC_CALLBACK_1(GameLevelCardHandler::onClick, this);
    }
    return nullptr;
}
Widget::ccWidgetEventCallback GameLevelCardHandler::onLocateEventCallback(const string &callBackName)
{
    if (callBackName == "onEvent")
    {
        return CC_CALLBACK_2(GameLevelCardHandler::onEvent, this);
    }
    return nullptr;
}
void GameLevelCardHandler::onTouch(cocos2d::Ref* object, cocos2d::ui::Widget::TouchEventType type)
{
    CCLOG("onTouch");
}
void GameLevelCardHandler::onClick(cocos2d::Ref* sender)
{
    
    Node* node = (Node*)sender;
    GameNodeInfo* gni = (GameNodeInfo*) node->getUserData();
    
    
    log("to level:%d  node:%d",gni->getGameLevelInfo()->getLevel(),gni->getNode());
    
    
    //加载音乐信息
    string musicFile = "music/stage/"+POPTStringUtils::intToString(gni->getGameLevelInfo()->getLevel())+"/"+gni->getMusic();
    
    
    auto musicModel = MusicModel::initWithFile(musicFile);
    
    gni->setMusicModel(musicModel);
    
    poptGlobal->gni = gni;

    auto scene = GuitarRun::createScene();
//    Scene* scene = StartScene::createScene();

    
    auto transition = TransitionCrossFade::create(0.5f, scene);
    Director::getInstance()->pushScene(transition);
}
void GameLevelCardHandler::onEvent(cocos2d::Ref* sender, int eventType)
{
    CCLOG("onEvent");
}