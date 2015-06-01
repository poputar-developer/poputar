//
//  Lyric.h
//  poputar
//
//  Created by allen on 15-5-29.
//
//

#ifndef __poputar__Lyric__
#define __poputar__Lyric__

#include <stdio.h>
#include "../../Model/LyricModel.h"
USING_NS_CC;
using namespace std;

class LyricText;

class Lyric:public Sprite{
private:
    map<string,LyricText*> textMap;
    
    lyricRunModel* lrm;
    
    float size;
public:
    static Lyric* createLyric(float size,lyricRunModel* lrm);
    
    void changeLyricText(lyricRunModel* lrm);
    
    void loadFrame();
    
    void lyricChangeColor(string key);
};

class LyricText :public Sprite{
private:

    LyricTonicModel* ltm;
    
    float size;
    
    Node* moveNode;
public:
    static LyricText* createLyricText(float size,LyricTonicModel* ltm);
    
    void loadFrame();
    
    void runLyricAction();
};

#endif /* defined(__poputar__Lyric__) */
