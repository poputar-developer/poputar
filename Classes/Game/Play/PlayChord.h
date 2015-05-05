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
#include "PlayConfig.h"

USING_NS_CC;
using namespace std;
class PlayChord :public ui::Scale9Sprite{
public:

    PlayConfig* config;
    
    BeatInfo* beatInfo;
    
    float x;
    
    
    static PlayChord* createPlayChord(BeatInfo* beatInfo,string fileName,float x);
    
    void loadFrame();
    
    float strToY(int str);
    
    void createBangingOut(string chordType, int startStr,int endStr);
    
};

#endif /* defined(__poputar__PlayChord__) */
