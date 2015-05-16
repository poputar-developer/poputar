
//
//  PopBaseLayer.h
//  poputar
//
//  Created by allen on 15-4-8.
//
//  弹出框的主页面基类
//

#ifndef __poputar__PopBaseLayer__
#define __poputar__PopBaseLayer__

#include <stdio.h>
USING_NS_CC;
class MenuBaseLayer : public LayerColor{
public:
    MenuBaseLayer();
    virtual ~MenuBaseLayer(){};
    void appear();
    void disappear();
    void close();
};
#endif /* defined(__poputar__PopBaseLayer__) */
