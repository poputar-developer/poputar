//
//  SelfTestScene.h
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#ifndef __poputar__SelfTestScene__
#define __poputar__SelfTestScene__

#include <stdio.h>
#include "GameLevelInfo.h"
#include "BaseLayer.h"
USING_NS_CC;

class SelfTestScene : public Layer{
private:
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    void loadTopFrame(float height);
    
    void loadFootFrame(float height);
    
    void goOnController(Ref* ref);

    void setBackground();
    
    
public:
    static Scene* createScene();

    CREATE_FUNC(SelfTestScene);
    
    virtual void goBack(Ref* sender);
};

#endif /* defined(__poputar__SelfTestScene__) */
