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
#include <stdio.h>
#include "cocos2d.h"
#include "Rhythm.h"
#include "Chord.h"
#include <MusicInfo.h>
#include "Lyric.h"
#include "Common.h"
#include "Chord.h"
USING_NS_CC;

class ChordRunLayer:public LayerColor{
private:
    //公告属性
    Common *common;
    //歌词
    Lyric *lyric;
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //开始动画
    void startAnimation();
    //创建和弦
    void getNewChords();
    //创建节奏线
    void getNewRhythm(bool first);
    //移动和弦
    void moveChords();
    //循环任务
    void rhythmMove(float dt);
    //碰撞检测方法
    void update(float dt);
    //发送蓝牙数据
    void sendDataToBluetooth();
    
public:
    virtual bool init(const Color4B &&color,MusicInfo *musicInfo);
    static ChordRunLayer *createChordRunLayer(MusicInfo *musicInfo);
    //返回时清空当前播放的参数
    void stopMusic();

};

#endif /* defined(__Guitars__MainLayer__) */
