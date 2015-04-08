//
//  GameMenu.h
//  poputar
//
//  Created by allen on 15-4-7.
//
//

#ifndef __poputar__GameMenu__
#define __poputar__GameMenu__

#include <cocos-ext.h>
#include <stdio.h>
#include "PopBaseLayer.h"
USING_NS_CC;

class GameMenuDelegate{
public:
    virtual void goOnCallback(Ref* ref)=0;
    virtual void restartCallback(Ref* ref)=0;
    virtual void goBackCallback(Ref* ref)=0;
};

class GameMenu : public PopBaseLayer{
private:
    void loadFrame();
    GameMenuDelegate* _delegate;
public:
    static GameMenu* createGameMenu();

    bool init();
    
    bool onTouchBegan(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch,Event* event);
    void onTouchEnded(Touch* touch,Event* event);
    
    void goOnController(Ref* ref);
    void restartController(Ref* ref);
    void goBackController(Ref* ref);
    
    void setDelegate(GameMenuDelegate* delegate);
};

#endif /* defined(__poputar__GameMenu__) */
