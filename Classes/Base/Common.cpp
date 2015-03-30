//
//  Common.cpp
//  Guitars
//
//  Created by allen on 14-12-27.
//
//

#include "Common.h"

Common * Common::common = NULL;

Common::~Common(){
    delete this->common;
}


Common * Common::getInstance(float contentWidth, float contentHeight, MusicInfo *musicInfo){
    if(!common){
        common = new Common();
        common->contentHeight = contentHeight;
        common->contentWidth = contentWidth;
        common->musicInfo=musicInfo;
        int beat = musicInfo->getBeat();
        common->unitWidth = contentWidth/(beat+common->leftUnit);
        common->unitHeight = contentHeight/common->unit4Y;
        common->unitSpeed = 60.0/musicInfo->getBpm();
        common->rhythm_time = common->unitSpeed * beat;
        common->rhythm_distance = common->unitWidth *beat;
        
        
        for (int i=1; i<=beat; i++) {
            float w = common->unitWidth*i;
            common->array4X.push_back(Value(w));
        }
        
        int unitHeightCount = common->unit4Y;
        for (int i=1; i<=unitHeightCount-1; i++) {
            float h =common->unitHeight*i;
            common->array4Y.push_back(Value(h));
        }
        
    }
    return common;
}

Common * Common::getInstance4Chord(float contentWidth,float contentHeight,MusicInfo *musicInfo){
    Common* common =  getInstance(contentWidth, contentHeight, musicInfo);
    int beat = musicInfo->getBeat();
    common->rhythm_time = common->unitSpeed * beat;
    return common;
}

Common* Common::getInstance4Finger(float contentWidth, float contentHeight, MusicInfo *musicInfo){
    Common* common =  getInstance(contentWidth, contentHeight, musicInfo);
    common->rhythm_time = common->unitSpeed;
    return common;
}

void Common::Release(){
    if(common != NULL){
        delete  common;
        common = NULL;
    }
}