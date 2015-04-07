//
//  GameConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "GameConfig.h"


GameConfig::GameConfig(float contentWidth, float contentHeight, MusicInfo *musicInfo){
    this->contentHeight = contentHeight;
    this->contentWidth = contentWidth;
    this->musicInfo = musicInfo;
    int bpm = musicInfo->getBpm();
    unitTime = 60.0/bpm;
}

GameConfig::~GameConfig(){
    this->musicInfo  = nullptr;
//    this->contentWidth = nullptr;
//    this->contentHeight = nullptr;
}