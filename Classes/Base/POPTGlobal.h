//
//  POPTGlobal.h
//  poputar
//
//  Created by allen on 15-4-14.
//
//

#ifndef __poputar__POPTGlobal__
#define __poputar__POPTGlobal__

#include <stdio.h>
#include "Singleton.h"
#include "GameLevelInfo.h"
#include "RunLayer.h"
USING_NS_CC;

class POPTGlobal:public Singleton<POPTGlobal>{
public:
    POPTGlobal(void);
    ~POPTGlobal(void);
    //游戏关卡信息
    GameNodeInfo* gni;
    //运行的游戏层信息
    RunLayer* runLayer;
    
};
#define poptGlobal POPTGlobal::instance()

#endif /* defined(__poputar__POPTGlobal__) */
