//
//  FingerConfig.h
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#ifndef __poputar__PlayConfig__
#define __poputar__PlayConfig__

#include <stdio.h>
#include "MusicModel.h"
#include "GameConfig.h"
USING_NS_CC;
//播放类型
#define PLAYTYPE 0 //正式播放
#define BLUETOOTHTYPE 1 //蓝牙传输

//试听控制
#define AUDITION_PLAY 0
#define AUDITION_STOP 1
#define AUDITION_PAUSE 3
#define AUDITION_RESUME 4

//小节类型
#define SECTION_FORMAL 0
#define SECTION_AUDITION 1



class PlayConfig: public GameConfig{
public:
    //音乐信息
    MusicModel *musicModel;
    
    //撞击线位置
    float impactLine = 50;
    //单元宽度
    float unitWidth=150;
    //小节循环周期
    float rhythmTime;
    //走完整个画面所需时间
    float contentWidthTime;
    //和弦区域宽度
    float rhythmWidth;
    //每秒需要移动距离
    double move4sec;
    //移动到撞击线的总时长
    double allTime;
    
    //弦的高度 用于生成扫弦块时的高度计算
//    float stringHeight;
    //弦之间的距离
    float unitHeight;
    
    float sectionWidth;
    
    
    PlayConfig(float contentWidth, float contentHeight, MusicModel *musicModel);

};

#endif /* defined(__poputar__FingerConfig__) */
