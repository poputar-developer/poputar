//
//  Fingering.h
//  Guitars
//
//  Created by allen on 14-12-28.
//
//

#ifndef __Guitars__Fingering__
#define __Guitars__Fingering__


#include <stdio.h>
#include "../Model/GameLevelInfo.h"
#include "ui/UIPageView.h"

using namespace std;
USING_NS_CC;
//USING_NS_CC_EXT;
using namespace cocos2d::ui;

class GameLevel : public Layer{
private:
    //进入游戏界面
    void toPlaySence(Ref* sender,GameNodeInfo* game);
    
    Node* currentLevel;
    Node* nextLevel;
    Node* nextTwoLevel;
    Node* lastLevel;
    Node* lastTwoLevel;
    
    PageView* pv;
    
    void musicLibBtnController(Ref* ref);
    
    void settingBtnController(Ref* ref);
public:
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(GameLevel);
    
    virtual bool init();
    
    virtual void onEnter();
    
    Node* getLevelInfo(int levelIndex,int nodeIndex);

    virtual void setBackground();
    
};

#endif /* defined(__Guitars__Fingering__) */
