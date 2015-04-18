//
//  ChordAnalysis.h
//  poputar
//  音乐信息翻译为蓝牙所需信息
//  Created by allen on 15-3-27.
//
//

#ifndef __poputar__ChordAnalysis__
#define __poputar__ChordAnalysis__

#include <stdio.h>
#include "Singleton.h"
USING_NS_CC;
using namespace std;

class MusicAnalysis:public Singleton<MusicAnalysis>{

public:
    
    MusicAnalysis(void);
    ~MusicAnalysis(void);
    //和弦解析为音符字符串
    void sendChordStr(string chord);
    
    //将字符串解析为二维数组并组装成为02命令的指令
    void sendMusicChar(string musical);
    
};
#define musicAnalysis MusicAnalysis::instance()
#endif /* defined(__poputar__ChordAnalysis__) */
