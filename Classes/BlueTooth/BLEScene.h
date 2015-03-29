//
//  BLEScene.h
//  Guitars
//  蓝牙连接界面
//  Created by allen on 15-3-17.
//
//

#ifndef __Guitars__BLEScene__
#define __Guitars__BLEScene__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"


USING_NS_CC;
using namespace std;
using namespace cocostudio::timeline;

class BLEScene : public Layer{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    void connectBle(float dt);
    
    void nextSence(float dt);
    
    CREATE_FUNC(BLEScene);
};

#endif /* defined(__Guitars__BLEScene__) */
