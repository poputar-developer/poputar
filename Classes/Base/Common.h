//
//  Common.h
//  Guitars
//
//  Created by allen on 14-12-27.
//
//

#ifndef __Guitars__Common__
#define __Guitars__Common__

#include <stdio.h>
#include "MusicInfo.h"

using namespace std;

class Common{

private:
    Common(){};
    static Common *common;
    
public:
    ~Common();
    //界面宽度
    float contentWidth;
    //界面高度
    float contentHeight;
    //音乐信息
    MusicInfo *musicInfo;
    //右侧多出的单元
    int leftUnit=1;
    //纵向单元数
    int unit4Y = 3;
    //单元宽度
    float unitWidth;
    //单元高度
    float unitHeight;
    //开始时间
    float startTime=3;
    //单元时间
    float unitSpeed;
    //循环周期
    float rhythm_time;
    //和弦区域宽度
    float rhythm_distance;
    //x轴坐标数组 定位和弦X轴位置和展示区域
    ValueVector array4X;
    //Y轴坐标数组 定位和弦Y轴位置
    ValueVector array4Y;
    
    static Common *getInstance(float contentWidth,float contentHeight,MusicInfo *music);
    static void Release();
};

#endif /* defined(__Guitars__Common__) */
