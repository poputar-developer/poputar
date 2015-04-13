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
    beat = 7;
    rhythm_time = unitTime;
    unitWidth = contentWidth/(beat+leftUnit);
    rhythm_distance = unitWidth *beat;
    int musicalSize = (int)musicInfo->getMusical().size();
    int beatCount = musicalSize/musicInfo->getBeat();
    if(musicalSize%musicInfo->getBeat()!=0){
        beatCount+=1;
    }
    musicTime = unitTime*beatCount*musicInfo->getBeat();
}