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
#include "../../Base/MaskBaseLayer.h"
USING_NS_CC;

class EndLayerDelegate{
public:
    virtual void endRestartCallback()=0;
    virtual void endNextCallback(bool isPassLevel)=0;
    virtual void endBackCallback(bool isPassLevel)=0;
};

class EndLayer: public MaskBaseLayer{
private:
    EndLayerDelegate* _delegate;
    void loadFrame(bool gameResult);
    bool isPassLevel;
public:
    static EndLayer* createEndLayer(bool gameReslut,bool isPassLevel);
    void restartController(Ref* ref);
    void nextController(Ref* ref);
    void backController(Ref* ref);
    
    void setDelegate(EndLayerDelegate* delegate);
};

#endif /* defined(__poputar__EndLayer__) */
