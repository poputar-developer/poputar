//
//
// 节奏线模型
//  Created by allen on 14-11-27.
//
//

#ifndef __Test1__GTRect__
#define __Test1__GTRect__

#include <stdio.h>
#include "cocos2d.h"
//#include "Common.h"
#include "ChordConfig.h"

USING_NS_CC;
using namespace std;

class Rhythm:public Sprite {

private:
    
    ActionInterval *move(ChordConfig *common,float time);
    
public:
    
    //是否真实节奏线（非歌曲开始前的节奏线，需要进行碰撞检测）
    bool isReal = true;
    
    virtual bool initWithFile(const string &filename,ChordConfig *common,int currentBeat);
    
    static Rhythm* createRhythm(ChordConfig *common,int currentBeat);

    ActionInterval *moveRhythm(ChordConfig *common);

    ActionInterval *firstMoveRhythm(ChordConfig *common);
    
    ActionInterval *leftMoveRhythm(ChordConfig *common);
};

#endif /* defined(__Test1__GTRect__) */
