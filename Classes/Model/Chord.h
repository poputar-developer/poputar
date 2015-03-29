//
//  Chord.h
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__Chord__
#define __Guitar__Chord__

#include <stdio.h>
#include "cocos2d.h"
#include "Common.h"
#include "SimpleAudioEngine.h"
#include "Lyric.h"

USING_NS_CC;

using namespace std;

class Chord:public Sprite{
private:
    string imageFilename;
    const char *voideFileName;
    string type;
public:
    
    bool isCollision=false;
    
    ~Chord();
    virtual bool initWithFile(string type,Common *common,int index);
    
    static Chord* createChord(Common *common,int index,string type,string lyric_str);
    
    void getFileNameWidthType(string type);
    
    ActionInterval * moveOut(Common *common);
    
    ActionInterval *moveToCurrent(Common *common);
    
    void collisionAction(Common *common);
    
    string getType();

};

#endif /* defined(__Guitar__Chord__) */
