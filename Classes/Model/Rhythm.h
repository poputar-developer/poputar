//
//  GTRect.h
//  Test1
//
//  Created by allen on 14-11-27.
//
//

#ifndef __Test1__GTRect__
#define __Test1__GTRect__

#include <stdio.h>
#include "cocos2d.h"
#include "Common.h"

USING_NS_CC;
using namespace std;

class Rhythm:public Sprite {

private:
    
    ActionInterval *move(Common *common,float time);
    
public:
    
    bool isReal = true;
    
    virtual bool initWithFile(const string &filename,Common *common,int currentBeat);
    
    static Rhythm* createRhythm(Common *common,int currentBeat);

    ActionInterval *moveRhythm(Common *common);

    ActionInterval *firstMoveRhythm(Common *common);
    
    ActionInterval *leftMoveRhythm(Common *common);
};

#endif /* defined(__Test1__GTRect__) */
