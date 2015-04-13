//
//  GameLevelInfo.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "GameLevelInfo.h"


void GameLevelInfo::setLevel(int level){
    this->level = level;
}

void GameLevelInfo::setNodes(vector<GameNodeInfo *> nodes){
    this->nodes = nodes;
}

int GameLevelInfo::getLevel(){
    return level;
}

vector<GameNodeInfo *> GameLevelInfo::getNodes(){
    return nodes;
}

void GameNodeInfo::setNode(int node){
    this->node = node;
}

void GameNodeInfo::setType(string type){
    this->type = type;
}

void GameNodeInfo::setMusic(string music){
    this->music = music;
}

void GameNodeInfo::setGameLevelInfo(GameLevelInfo *gli){
    this->gameLevelInfo = gli;
}

void GameNodeInfo::setMusicInfo(MusicInfo *mi){
    this->musicInfo = mi;
}

int GameNodeInfo::getNode(){
    return node;
}

string GameNodeInfo::getType(){
    return type;
}

string GameNodeInfo::getMusic(){
    return music;
}

GameLevelInfo* GameNodeInfo::getGameLevelInfo(){
    return gameLevelInfo;
}

MusicInfo* GameNodeInfo::getMusicInfo(){
    return musicInfo;
}
