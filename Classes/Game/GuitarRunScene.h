//
//  GuitarRunScene.h
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__GuitarRunScene__
#define __Guitar__GuitarRunScene__

#include <stdio.h>
#include "cocos2d.h"
#include <MusicInfo.h>
#include "BaseLayer.h"
#include "GameInfo.h"
USING_NS_CC;

class GuitarRun: public BaseLayer{
  

private:
    public:
    static Scene *createScene(MusicInfo *musicInfo,GameInfo *gameInfo);
    
    void startChordMusic(MusicInfo *musicInfo);
    void startFingerMusic(MusicInfo *musicInfo);
    
    CREATE_FUNC(GuitarRun);

    void goBack(Ref* sender);
};




#endif /* defined(__Guitar__GuitarRunScene__) */
