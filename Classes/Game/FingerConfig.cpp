//
//  FingerConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "FingerConfig.h"

FingerConfig::FingerConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo):GameConfig(contentWidth,contentHeight,musicInfo){
    initialise();
};


void FingerConfig::initialise(){
    unitSpeed = 60.0/musicInfo->getBpm();
    rhythm_time = unitSpeed;
    unitWidth = contentWidth/(beat+leftUnit);
//    unitHeight = contentHeight/unit4Y;
    rhythm_distance = unitWidth *beat;
}