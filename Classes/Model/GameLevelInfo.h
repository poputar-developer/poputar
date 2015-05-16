//
//  GameLevelInfo.h
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#ifndef __poputar__GameLevelInfo__
#define __poputar__GameLevelInfo__

#include <stdio.h>
#include "MusicModel.h"
#include "GameConfig.h"
using namespace std;

class GameNodeInfo;

class GameLevelInfo{
private:
    int level;
    string title;
    vector<GameNodeInfo*> nodes;
public:
    void setLevel(int level);
    void setTitle(string title);
    void setNodes(vector<GameNodeInfo*> node);
    int getLevel();
    string getTitle();
    vector<GameNodeInfo*> getNodes();
};

class GameNodeInfo{
private:
    int node;
    string music;
    GameLevelInfo* gameLevelInfo;
    MusicModel* musicModel;
    GameConfig* config;
    
public:
    void setNode(int node);
//    void setType(string type);
    void setMusic(string music);
    void setGameLevelInfo(GameLevelInfo* gli);
//    void setMusicInfo(MusicInfo* mi);
    void setMusicModel(MusicModel* mm);
    void setConfig(GameConfig* config);
    
    int getNode();
//    string getType();
    string getMusic();
    GameLevelInfo* getGameLevelInfo();
//    MusicInfo* getMusicInfo();
    MusicModel* getMusicModel();
    GameConfig* getConfig();
};

#endif /* defined(__poputar__GameLevelInfo__) */
