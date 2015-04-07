//
//  ChordConfig.h
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#ifndef __poputar__ChordConfig__
#define __poputar__ChordConfig__

#include <stdio.h>
#include "GameConfig.h"
USING_NS_CC;
class ChordConfig : public GameConfig{
public:
    //右侧多出的单元
    int leftUnit=1;
    //纵向单元数
    int unit4Y = 3;
    //单元宽度
    float unitWidth;
    //单元高度
    float unitHeight;
    //循环周期
    float rhythm_time;
    //和弦区域宽度
    float rhythm_distance;
    //x轴坐标数组 定位和弦X轴位置和展示区域
    ValueVector array4X;
    //Y轴坐标数组 定位和弦Y轴位置
    ValueVector array4Y;

    int beat;
    
    ChordConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo);
    ~ChordConfig();
    
    virtual void initialise(MusicInfo *musicInfo);

};

#endif /* defined(__poputar__ChordConfig__) */
