//
//  MaskBaseLayer.h
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#ifndef __poputar__MaskBaseLayer__
#define __poputar__MaskBaseLayer__

#include <stdio.h>
USING_NS_CC;

class MaskBaseLayer:public LayerColor{
public:
    static MaskBaseLayer* createMaskBaseLayer();
    
    bool initWithColor(const Color4B& color);
    
    bool onTouchBegan(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch,Event* event);
    void onTouchEnded(Touch* touch,Event* event);
    
};

#endif /* defined(__poputar__MaskBaseLayer__) */
