//
//  ChordConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "ChordConfig.h"

ChordConfig::ChordConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo):GameConfig(contentWidth,contentHeight,musicInfo){
    initialise(musicInfo);
};

ChordConfig::~ChordConfig(){
    array4X.clear();
    array4Y.clear();
}

void ChordConfig::initialise(MusicInfo *musicInfo){
    beat = musicInfo->getBeat();

    rhythm_time = unitTime * beat;
    unitWidth = contentWidth/(beat+leftUnit);
    unitHeight = contentHeight/unit4Y;
    rhythm_time = unitTime * beat;
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
    
    int chordSize = musicInfo->getChords().size()*beat;
    int beatCount = chordSize/musicInfo->getBeat();
    if(chordSize%musicInfo->getBeat()!=0){
        beatCount+=1;
    }
    musicTime = unitTime*beatCount*beat;
}