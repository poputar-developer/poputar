//
//  GameLevelSingleton.h
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#ifndef __poputar__GameLevelSingleton__
#define __poputar__GameLevelSingleton__


#define CURR_LEVEL_KEY "level"

#define CURR_NODE_KEY "node"

#include <stdio.h>
#include "Singleton.h"
#include "cocostudio/CocoStudio.h"
#include "GameLevelInfo.h"
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
