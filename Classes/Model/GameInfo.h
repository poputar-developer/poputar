//
//  GameInfo.h
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#ifndef __poputar__GameInfo__
#define __poputar__GameInfo__

#include <stdio.h>
using namespace std;
class GameInfo{
private:
    int level;
    int node;
    string type;
    string music;
    string chord;
public:
    void setLevel(int level);
    void setNode(int node);
    void setType(string type);
    void setMusic(string music);
    void setChord(string chord);
    
    int getLevle();
    int getNode();
    string getType();
    string getMusic();
    string getChord();
    
};

#endif /* defined(__poputar__GameInfo__) */
