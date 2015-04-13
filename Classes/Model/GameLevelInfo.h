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
#include "MusicInfo.h"
using namespace std;

class GameNodeInfo;

class GameLevelInfo{
private:
    int level;
    vector<GameNodeInfo*> nodes;
public:
    void setLevel(int level);
    void setNodes(vector<GameNodeInfo*> node);
    int getLevel();
    vector<GameNodeInfo*> getNodes();
};

class GameNodeInfo{
private:
    int node;
    string type;
    string music;
    GameLevelInfo* gameLevelInfo;
    MusicInfo* musicInfo;
    
public:
    void setNode(int node);
    void setType(string type);
    void setMusic(string music);
    void setGameLevelInfo(GameLevelInfo* gli);
    void setMusicInfo(MusicInfo* mi);
    
    int getNode();
    string getType();
    string getMusic();
    GameLevelInfo* getGameLevelInfo();
    MusicInfo* getMusicInfo();
};

#endif /* defined(__poputar__GameLevelInfo__) */
