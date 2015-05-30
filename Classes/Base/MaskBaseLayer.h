//
//  MaskBaseLayer.h
//  poputar
//
//  Created by allen on 15-4-13.
// 弹出遮罩层
//

#ifndef __poputar__MaskBaseLayer__

#define MASK_BASE_LAYER 1
#define MASK_WIDGET_LAYER 2

#define __poputar__MaskBaseLayer__

#include <stdio.h>
USING_NS_CC;

class MaskBaseLayer:public LayerColor{
public:
    
    bool initWithColor(const Color4B& color);
    
};

#endif /* defined(__poputar__MaskBaseLayer__) */
