//
//  ChordAnalysis.h
//  poputar
//
//  Created by allen on 15-3-27.
//
//

#ifndef __poputar__ChordAnalysis__
#define __poputar__ChordAnalysis__

#include <stdio.h>
USING_NS_CC;
using namespace std;

class MusicAnalysis{
private:
    MusicAnalysis(){};
    static MusicAnalysis* ma;
    
public:
    
    static MusicAnalysis* getInstance();
    
    //和弦解析为音符字符串
    unsigned char* sendChordStr(string chord);
    
    //将字符串解析为二维数组并组装成为02命令的指令
    unsigned char* sendMusicChar(string musical);
    
};

#endif /* defined(__poputar__ChordAnalysis__) */
