//
//  LyricModel.h
//  poputar
//
//  Created by allen on 15-5-24.
//
//

#ifndef __poputar__LyricModel__
#define __poputar__LyricModel__

#include <stdio.h>
using namespace std;

class LyricPlayModel;
class LyricSectionModel;
class LyricTonicModel;
class lyricRunModel;


class LyricModel{
private:
    map<int,LyricPlayModel*> lyricPlayMap;
    
    map<int,lyricRunModel*> lyricContentMap;
public:
    static LyricModel* initWithFile(string fileName);
    map<int,LyricPlayModel*> getPlayMap();
    map<int,lyricRunModel*> getContentMap();
    void unLoadLyric();
};

class LyricPlayModel{
public:
//    int p_index;
    map<int,LyricSectionModel*> lyricSectionMap;
};

class LyricSectionModel{
public:
//    int s_index;
    map<int,LyricTonicModel*> lyricTonicMap;
};

class LyricTonicModel{
public:
//    int t_index;
    float lenght;
    string content;
};

class lyricRunModel{
public:
    int s_pIndex;
    int s_sIndex;
    int s_tIndex;
    int e_pIndex;
    int e_sIndex;
    int e_tIndex;
    string content;
};

#endif /* defined(__poputar__LyricModel__) */
