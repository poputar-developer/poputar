//
//  ChordConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "ChordConfig.h"

ChordConfig::ChordConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo):GameConfig(contentWidth,contentHeight,musicInfo){
    initialise();
};

ChordConfig::~ChordConfig(){
    array4X.clear();
    array4Y.clear();
}

void ChordConfig::initialise(){
    int beat = musicInfo->getBeat();
    unitSpeed = 60.0/musicInfo->getBpm();
    rhythm_time = unitSpeed * beat;
    unitWidth = contentWidth/(beat+leftUnit);
    unitHeight = contentHeight/unit4Y;
    rhythm_time = unitSpeed * beat;
    rhythm_distance = unitWidth *beat;
    
    array4X.clear();
    array4Y.clear();
    for (int i=1; i<=beat; i++) {
        float w = unitWidth*i;
        array4X.push_back(Value(w));
    }
    
    int unitHeightCount = unit4Y;
    for (int i=1; i<=unitHeightCount-1; i++) {
        float h =unitHeight*i;
        array4Y.push_back(Value(h));
    }
}