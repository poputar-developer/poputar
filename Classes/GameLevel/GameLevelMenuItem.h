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
    //段位
    int level;
    //关卡
    int node;
    //是否锁定
    bool isLocked;
    
public:
    //新建关卡按钮
    /**
     isLocked 是否锁定
     level 当前段位
     node 当前关卡
     callback回调方法
     */
    static GameLevelMenuItem* createGameLevelMenuItem(bool isLocked,int level,int node,const ccMenuCallback& callback);
};


#endif /* defined(__Guitars__LevelSprite__) */
