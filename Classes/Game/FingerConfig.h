//
//  FingerConfig.h
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#ifndef __poputar__FingerConfig__
#define __poputar__FingerConfig__

#include <stdio.h>
#include "GameConfig.h"
USING_NS_CC;
class FingerConfig : public GameConfig{
public:
    //左侧份数（消失的空间）
    int leftUnit=1;
    //右侧份数（音符移动空间）
    float beat =7;
    //单元宽度
    float unitWidth;
    //单元时间 音符间隔时间
    float unitSpeed;
    //音符移动时间的基数
    float speedBase = 4;
    //循环周期
    float rhythm_time;
    //和弦区域宽度
    float rhythm_distance;
    
    
    FingerConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo);
    
    virtual void initialise();

};

#endif /* defined(__poputar__FingerConfig__) */
