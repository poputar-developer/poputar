//
//  GameLevelSingleton.h
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#ifndef __poputar__GameLevelSingleton__
#define __poputar__GameLevelSingleton__

//大阶段标识
#define CURR_LEVEL_KEY "level"
//阶段内关卡标识
#define CURR_NODE_KEY "node"

#include <stdio.h>
#include "../Base/Singleton.h"
#include "../Model/GameLevelInfo.h"
using namespace std;
USING_NS_CC;
class GameLevelSingleton:public Singleton<GameLevelSingleton>{
public:
    GameLevelSingleton(void);
    ~GameLevelSingleton(void);
    vector<GameLevelInfo*> levels;
};
#define gameLevelSingleton GameLevelSingleton::instance()
#endif /* defined(__poputar__GameLevelSingleton__) */
