//
//  GameInfo.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "GameInfo.h"


void GameInfo::setLevel(int level){
    this->level = level;
}

void GameInfo::setNode(int node){
    this->node = node;
}

void GameInfo::setType(string type){
    this->type = type;
}

void GameInfo::setMusic(string music){
    this->music = music;
}

void GameInfo::setChord(string chord){
    this->chord = chord;
}

int GameInfo::getLevle(){
    return this->level;
}

int GameInfo::getNode(){
    return this->node;
}

string GameInfo::getType(){
    return this->type;
}

string GameInfo::getMusic(){
    return this->music;
}

string GameInfo::getChord(){
    return this->chord;
}