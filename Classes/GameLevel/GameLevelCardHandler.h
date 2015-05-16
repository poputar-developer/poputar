//
//  GameLevelCardHandler.h
//  poputar
//
//  Created by allen on 15-5-9.
//
//

#ifndef __poputar__GameLevelCardHandler__
#define __poputar__GameLevelCardHandler__

#include <stdio.h>
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "cocostudio/WidgetCallBackHandlerProtocol.h"
#include "GameRunScene.h"

class GameLevelCardHandler:public cocos2d::Node,public cocostudio::WidgetCallBackHandlerProtocol{
public:
    CREATE_FUNC(GameLevelCardHandler);
    GameLevelCardHandler();
    virtual cocos2d::ui::Widget::ccWidgetTouchCallback onLocateTouchCallback(const std::string &callBackName);
    virtual cocos2d::ui::Widget::ccWidgetClickCallback onLocateClickCallback(const std::string &callBackName);
    virtual cocos2d::ui::Widget::ccWidgetEventCallback onLocateEventCallback(const std::string &callBackName);
    void onTouch(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void onClick(cocos2d::Ref* sender);
    void onEvent(cocos2d::Ref* sender, int eventType);
private:
    std::vector<std::string> _touchTypes;
    std::string _click;
    std::vector<std::string> _eventTypes;
};
#endif /* defined(__poputar__GameLevelCardHandler__) */
