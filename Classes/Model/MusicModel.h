//
//  MusicModel.h
//  poputar
//
//  Created by allen on 15-4-27.
//
//

#ifndef __poputar__MusicModel__
#define __poputar__MusicModel__

#include <stdio.h>
#include "LyricModel.h"

USING_NS_CC;

//音乐类型 -- 和弦
#define MUSICMODEL_TYPE_CHORD "CHORD"
//音乐类型 -- 主音
#define MUSICMODEL_TYPE_TONIC "TONIC"

using namespace std;

class BeatInfo;

class TonicInfo;

class MusicPlayInfo;

class SectionInfo;

class MusicModel{
private:
    string type; //音乐类型
    string key;
    string title; //标题
    int beatRef;//以及分音符为一拍
    int beatFlag; //每小节拍数
    float bpm; //速度
    map<int,MusicPlayInfo*> plays; //循环方式
    map<int,SectionInfo*> sections;//小节信息
    LyricModel * lyricModel; //歌词信息
    
public:
    static MusicModel* initWithFile(string fileName);
    string getType();
    string getTitle();
    int getBeatFlag();
    int getBeatRef();
    int getBpm();
    string getKey();
    map<int,SectionInfo*> getSections();
    map<int,MusicPlayInfo*> getPlayInfo();
    
    LyricModel* getLyricModel();
    
    void unLoadMusicModel();
    
};

/*
 小节信息
 */
class SectionInfo{
public:
    int s_index; //索引
    map<int,TonicInfo*> tonics;//主音信息
//    vector<TonicInfo*> tonics; //主音信息
    map<int,BeatInfo*>beats; //和弦信息
};

/*
 和弦信息
 */
class BeatInfo{
public:
    int b_index; //索引
    string chordType; //和弦类型
    double length; //长度 与主音长度一致
    string play; //播放方式 为当前和弦扫弦的方式，同时拨当前和弦的某些弦，以“@|@”分割.例:拨1到6弦->1@|@2@|@3@|@4@|@5@|@6
    string stringInfo; //弹奏特殊音 与和弦类型、播放方式无关，拨响对应弦的对应品，如播放方式次标识冲突，则以此标识为准。 例：拨1弦0品和2弦1品->1:0@|@2:1
};

/*
 主音信息
 */
class TonicInfo{
public:
    int t_index; //索引
    string note; //音符
    double length; //音符类型 拍数二分之一 = 0.5   拍数四分之一 = 0.25
    //四分之一音符为1拍，则1表示四分之音符，0.5表示八分之一音符
};

/*
 音乐循环模式
 */
class MusicPlayInfo{
public:
    int p_index; //索引
    int startSection; //开始小节
    int endSection; //结束小节
};

#endif /* defined(__poputar__MusicModel__) */
