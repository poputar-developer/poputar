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
    //key:第几句歌词  value:歌词内容信息
    map<int,lyricRunModel*> lyricContentMap;
public:
    static LyricModel* initWithFile(string fileName);
    map<int,lyricRunModel*> getContentMap();
//    map<int,LyricPlayModel*> getPlayMap();
//    LyricTonicModel* getTonicModel(int p,int s,int t);
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
    int p_index;
    int s_index;
    int t_index;
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
    
    vector<LyricTonicModel*> contentVec;
};

#endif /* defined(__poputar__LyricModel__) */
