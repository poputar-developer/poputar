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
#include <cocos-ext.h>
#include <ui/CocosGUI.h>
#include "BaseLayer.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class GameLevel : public BaseLayer{
private:
    //组装界面
    void loadFrame();
    //进入游戏界面
    void toPlaySence(Ref* sender);
public:
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(GameLevel);

    virtual void setBackground();
    
};

#endif /* defined(__Guitars__Fingering__) */
