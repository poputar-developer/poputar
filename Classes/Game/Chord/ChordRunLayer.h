//
//  MainLayer.h
//  Guitars
//
//  Created by allen on 14-12-23.
//
//

#ifndef __Guitars__MainLayer__
#define __Guitars__MainLayer__

#include <stdio.h>
#include "Rhythm.h"
#include "Chord.h"
#include "Lyric.h"
//#include "Common.h"
#include "RunLayer.h"
#include "ChordConfig.h"
USING_NS_CC;

class ChordRunLayer:public RunLayer{
private:
    ChordConfig *chordConfig;
    //歌词
    Lyric *lyric;
    //创建和弦
    void getNewChords(int currentBeat,bool isWait);
    //创建节奏线
    void getNewRhythm(bool first);
    //移动和弦
    void moveChords();
    //循环任务
    void rhythmMove(float dt);
    //碰撞检测方法
    void update(float dt);
    //节拍器
    void metronome(float dt);
 
    
public:
    bool init4Chord(const Color4B &color,MusicInfo *musicInfo);
    static ChordRunLayer *createChordRunLayer(MusicInfo *musicInfo);
    //发送蓝牙数据
    virtual void sendDataToBluetooth();
    //返回时清空当前播放的参数
    virtual void stopMusic();
    
    virtual void endAnimationSetting();
    
    virtual void restart(int musicalIndex);

};

#endif /* defined(__Guitars__MainLayer__) */
