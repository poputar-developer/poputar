//
//  BaseLayer.h
//  Guitars
//
//  Created by allen on 15-3-24.
//
//

#ifndef __Guitars__BaseLayer__
#define __Guitars__BaseLayer__

#include <stdio.h>
#include <cocos-ext.h>
USING_NS_CC;

class BaseLayer : public Layer{
    
public:
    virtual bool init();
    virtual void goBack(Ref* sender);
    virtual void setBackground();
    
};

#endif /* defined(__Guitars__BaseLayer__) */
