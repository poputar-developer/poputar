//
//  BaseLayer.h
//  Guitars
//
//  Created by allen on 15-3-24.
//
//  默认的Layer基类，自带返回按钮和背景

#ifndef __Guitars__BaseLayer__
#define __Guitars__BaseLayer__

#include <stdio.h>
#include <cocos-ext.h>
USING_NS_CC;

class BaseLayer : public Layer{
    
public:
    virtual bool init();
    //回到上一场景
    virtual void goBack(Ref* sender);
    //设置背景
    virtual void setBackground();
    
};

#endif /* defined(__Guitars__BaseLayer__) */
