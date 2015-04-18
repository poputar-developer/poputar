//
//  FingerConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "FingerConfig.h"

FingerConfig::FingerConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo):GameConfig(contentWidth,contentHeight,musicInfo){
    initialise(musicInfo);
};


void FingerConfig::initialise(MusicInfo *musicInfo){
    rhythm_time = unitTime;
    unitWidth = contentWidth/(beat+leftUnit);
    rhythm_distance = unitWidth *beat;
    int musicalSize = (int)musicInfo->getMusical().size();
    int beatCount = musicalSize/musicInfo->getBeat();
    if(musicalSize%musicInfo->getBeat()!=0){
        beatCount+=1;
    }
    
    //beatCount = (int)musicInfo->sections.size();
    
    //音乐总长度（音符间的时间 * 小节数 * 每小节音阶个数+开始的8个空音符）
    musicTime = unitTime*beatCount*musicInfo->getBeat()+unitTime*musicInfo->getBeat();
    
}