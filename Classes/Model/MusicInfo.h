//
//  MusicInfo.h
//  Guitar
//  音乐模型类
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__MusicInfo__
#define __Guitar__MusicInfo__

#include <stdio.h>
#include <list>
#include <string>

USING_NS_CC;
using namespace std;

//class MusicalInfo;
//
//class SectionInfo;

class MusicInfo{
private:
    float bpm;
    //小节拍数
    int beat;
    //和弦列表
    ValueVector vec_chords;
    //歌词
    ValueVector vec_lyric;
    //弹唱的位置信息
    ValueVector vec_musical;
    string title;
    string musicFile;
     vector<string> bluetoothChord;
    
public:
   
    static MusicInfo* initWithJson(string uuid);
    int getBeat();
    int getBpm();
    ValueVector getChords();
    ValueVector getLyircs();
    ValueVector getMusical();
    vector<string> getBluetoothChord();
//    vector<SectionInfo*> sections;
    
    string getTitle();
    string getMusicFile();
    
};

//
//class SectionInfo{
//public:
//    string chordInfo;
//    vector<MusicalInfo*> musicals;
//};
//
//class MusicalInfo{
//public:
//    float beat;
//    string stringInfo;
//};

#endif /* defined(__Guitar__MusicInfo__) */
