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
public:
    
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(GameLevel);
    
    void loadFrame();
    
    void toPlaySence(Ref* sender);
    
    
    virtual void setBackground();
    
};

#endif /* defined(__Guitars__Fingering__) */
