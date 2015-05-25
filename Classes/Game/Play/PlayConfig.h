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
//#include "GameConfig.h"
USING_NS_CC;
//播放类型
#define UPDATE_TYPE_CHORD 0 //正式播放
#define UPDATE_TYPE_TONIC 1
#define UPDATE_TYPE_BLUETOOTH 2 //蓝牙传输

//试听控制
#define AUDITION_PAUSE 0
#define AUDITION_RESUME 1

//小节类型
//展示和弦
#define SECTION_FORMAL_CHORD 0
//展示主音
#define SECTION_FORMAL_TONIC 1
//试听
#define SECTION_AUDITION 2
//展示（仅展示节奏线 正式的前置后置小节）
#define SECTION_SHOW 3
//空(试听的前置后置小节）
#define SECTION_NONE 4





class PlayConfig{
public:
    
    //界面宽度
    float contentWidth;
    //界面高度
    float contentHeight;
    //单元时间 音符间隔时间
    float unitTime;
    //歌曲总时长
    float musicTime;
    //结尾增加的时间
    float endTime=1;
    
    
    //音乐信息
    MusicModel *musicModel;
    
    //撞击线位置
    float impactLine = 100;
    //单元宽度
    float unitWidth=300;
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
    //和弦展示的高度
    float chordHeight;
    //弦的区域高度
    float stringsHeight;
    //弦距离上下的高度
    float stringSideHeight=30.0f;
    //和弦间的高度
    float stringUnitHeight;
    //开始动画时移动的距离
    float countdownWidth;
    //小节宽度
    float sectionWidth;
    //前置和弦的个数
    int beforSectionSize;
    //和弦层起始位置
    int startX;
    //后置和弦个数
    int afterSectionSize;
    
    
    PlayConfig(float contentWidth, float contentHeight, MusicModel *musicModel);

};

#endif /* defined(__poputar__FingerConfig__) */
