//
//  EndLayer.h
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#ifndef __poputar__EndLayer__
#define __poputar__EndLayer__

#include <cocos-ext.h>
#include <stdio.h>
#include "MenuBaseLayer.h"
USING_NS_CC;

class EndLayerDelegate{
public:
    virtual void endRestartCallback()=0;
    virtual void endNextCallback()=0;
};

class EndLayer: public LayerColor{
private:
    EndLayerDelegate* _delegate;
    void loadFrame();
public:
    static EndLayer* createEndLayer();
    
    bool initWithColor(const Color4B& color);
    
    bool onTouchBegan(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch,Event* event);
    void onTouchEnded(Touch* touch,Event* event);
    
    void restartController(Ref* ref);
    void nextController(Ref* ref);
    
    void setDelegate(EndLayerDelegate* delegate);
};

#endif /* defined(__poputar__EndLayer__) */
