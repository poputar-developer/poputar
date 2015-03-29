//
//  SelectMusic.h
//  Guitars
//
//  Created by allen on 15-1-26.
//
//

#ifndef __Guitars__SelectMusic__
#define __Guitars__SelectMusic__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"



USING_NS_CC;
using namespace std;
using namespace cocostudio::timeline;

class SelectMusic : public cocos2d::Layer{
    
 
public:

    void toFingering(Ref* sender);
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(SelectMusic);
};

#endif /* defined(__Guitars__SelectMusic__) */
