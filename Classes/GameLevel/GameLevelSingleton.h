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
#include "cocostudio/CocoStudio.h"
#include "GameLevelInfo.h"
using namespace std;
USING_NS_CC;
class GameLevelSingleton{
private:
    vector<GameLevelInfo*> levels;
    
    GameLevelSingleton(){};
    
    static GameLevelSingleton* instance;
    
    void init();
    
    
public:
    static GameLevelSingleton* getInstance();
    
    vector<GameLevelInfo*> getLeves();
};

#endif /* defined(__poputar__GameLevelSingleton__) */
