//
//  MusicalBackground.h
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#ifndef __poputar__MusicalBackground__
#define __poputar__MusicalBackground__

#include <stdio.h>
#include "FingerConfig.h"
#include <cocos-ext.h>
#include "MusicInfo.h"
USING_NS_CC;
using namespace std;
class MusicalBackground : public Sprite{
private:
    static void loadFrame(MusicalBackground *item,FingerConfig *config,float oneY,float sixY);
public:
    static float secMove;
    static MusicalBackground *createMusicalBackground(FingerConfig *config,float oneY,float sixY);
    
    ActionInterval* MucsicalBackgroundMove(FingerConfig *config);
    
    void createMusical(MusicInfo *musicInfo,ValueMapIntKey stringMap);
    
    float getSecMove(FingerConfig * config);
};

#endif /* defined(__poputar__MusicalBackground__) */
