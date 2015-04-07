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
#include "FingerConfig.h"
#include "Musical.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

using namespace std;
class FingerRunLayer : public RunLayer{
private:
    
    //弦之间的距离
    float unitHeight;
    //配置信息
    FingerConfig *fingerConfig;
    //组装画面
    void loadFrame();
    //初始化开始的音符
    void startMusical(int musicalIndex);
    //音符开始移动
    void musicalMove(float at);
    //碰撞检测
    void update(float at);
    
public:
    bool init4Finger(const Color4B &&color,MusicInfo *musicInfo);
    static FingerRunLayer *createFingerRunLayer(MusicInfo *musicInfo);
    virtual void stopMusic();
    virtual void endAnimationSetting();
    virtual void sendDataToBluetooth();
    virtual void restart(int musicalIndex);
};
#endif /* defined(__poputar__FingerRunLayer__) */
