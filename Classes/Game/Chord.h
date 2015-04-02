//
//  Chord.h
//  Guitar
//  和弦模型类
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__Chord__
#define __Guitar__Chord__

#include <stdio.h>
#include "cocos2d.h"
#include "ChordConfig.h"
#include "SimpleAudioEngine.h"
#include "Lyric.h"
#include "ChordConfig.h"

USING_NS_CC;

using namespace std;

class Chord:public Sprite{
private:
    string imageFilename;
    const char *voideFileName;
    string type;
public:
    
    //是否需要碰撞检测
    bool isCollision=false;
    
    ~Chord();
    virtual bool initWithFile(string type,ChordConfig *chordConfig,int index);
    
    static Chord* createChord(ChordConfig *chordConfig,int index,string type,string lyric_str);
    
    void getFileNameWidthType(string type);
    
    ActionInterval * moveOut(ChordConfig *chordConfig);
    
    ActionInterval *moveToCurrent(ChordConfig *chordConfig);
    
    void collisionAction(ChordConfig *chordConfig);
    
    string getType();

};

#endif /* defined(__Guitar__Chord__) */
