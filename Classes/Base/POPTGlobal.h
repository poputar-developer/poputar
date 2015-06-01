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
#include "../Model/GameLevelInfo.h"
#include "../Game/Play/PlayRunLayer.h"
USING_NS_CC;

class POPTGlobal:public Singleton<POPTGlobal>{
public:
    POPTGlobal(void);
    ~POPTGlobal(void);
    //游戏关卡信息
    GameNodeInfo* gni;
    //运行的游戏层信息
    PlayRunLayer* runLayer;
    //游戏配置信息
    PlayConfig* config;
    
};
#define poptGlobal POPTGlobal::instance()

#endif /* defined(__poputar__POPTGlobal__) */
