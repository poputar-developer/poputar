//
//  LevelSprite.h
//  Guitars
//
//  Created by allen on 15-3-23.
//
//

#ifndef __Guitars__LevelSprite__
#define __Guitars__LevelSprite__

#include <stdio.h>
#include <cocos-ext.h>


USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class GameLevelMenuItem : public MenuItemSprite{
private:
    int level;
    int node;
    
    bool isLocked;
    
public:
    
    static GameLevelMenuItem* createGameLevelMenuItem(bool isLocked,int level,int node,const ccMenuCallback& callback);
};


#endif /* defined(__Guitars__LevelSprite__) */
