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

void GameLevelInfo::setTitle(string title){
    this->title = title;
}

void GameLevelInfo::setNodes(vector<GameNodeInfo *> nodes){
    this->nodes = nodes;
}

int GameLevelInfo::getLevel(){
    return level;
}

string GameLevelInfo::getTitle(){
    return title;
}

vector<GameNodeInfo *> GameLevelInfo::getNodes(){
    return nodes;
}

void GameNodeInfo::setNode(int node){
    this->node = node;
}

void GameNodeInfo::setMusic(string music){
    this->music = music;
}

void GameNodeInfo::setGameLevelInfo(GameLevelInfo *gli){
    this->gameLevelInfo = gli;
}

void GameNodeInfo::setMusicModel(MusicModel *mm){
    this->musicModel = mm;
}

void GameNodeInfo::setConfig(PlayConfig *config){
    this->config = config;
}

int GameNodeInfo::getNode(){
    return node;
}

string GameNodeInfo::getMusic(){
    return music;
}

GameLevelInfo* GameNodeInfo::getGameLevelInfo(){
    return gameLevelInfo;
}


MusicModel* GameNodeInfo::getMusicModel(){
    return musicModel;
}

PlayConfig* GameNodeInfo::getConfig(){
    return config;
}