//
//  FingerRunLayer.h
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#ifndef __poputar__FingerRunLayer__
#define __poputar__FingerRunLayer__

#include <stdio.h>

#include <cocos-ext.h>
#include "RunLayer.h"
USING_NS_CC;

using namespace std;
class FingerRunLayer : public RunLayer{
private:
    
    int speed;
    //组装画面
    void loadFrame();
    //音符开始移动
    void musicalMove(float at);
public:
    bool init4Finger(const Color4B &&color,MusicInfo *musicInfo);
    static FingerRunLayer *createFingerRunLayer(MusicInfo *musicInfo);
    virtual void stopMusic();
    virtual void endAnimationSetting();
};
#endif /* defined(__poputar__FingerRunLayer__) */
