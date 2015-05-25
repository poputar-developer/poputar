//
//  EndLayer.h
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#ifndef __poputar__EndLayer__
#define __poputar__EndLayer__

#include <stdio.h>
#include "MaskBaseLayer.h"
USING_NS_CC;

class EndLayerDelegate{
public:
    virtual void endRestartCallback()=0;
    virtual void endNextCallback()=0;
    virtual void endBackCallback()=0;
};

class EndLayer: public MaskBaseLayer{
private:
    EndLayerDelegate* _delegate;
    void loadFrame();
public:
    static EndLayer* createEndLayer();
    void restartController(Ref* ref);
    void nextController(Ref* ref);
    void backController(Ref* ref);
    
    void setDelegate(EndLayerDelegate* delegate);
};

#endif /* defined(__poputar__EndLayer__) */
