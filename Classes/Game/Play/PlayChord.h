//
//  PlayChord.h
//  poputar
//
//  Created by allen on 15-4-29.
//
//

#ifndef __poputar__PlayChord__
#define __poputar__PlayChord__

#include <stdio.h>
#include <cocos-ext.h>
#include "MusicModel.h"
#include "PlayInfo.h"
USING_NS_CC;
using namespace std;
class PlayChord :public ui::Scale9Sprite,public PlayInfo{
public:
    
    BeatInfo* beatInfo;
    
    float x;
    
    static PlayChord* createPlayChord(BeatInfo* beatInfo,string lineFileName,string circleFileName,float x);
    
    void loadFrame(string circleFileName);
    
    
    
    void createBangingOut(string chordType, int startStr,int endStr,int upOrDownFlag);
    
};

#endif /* defined(__poputar__PlayChord__) */
