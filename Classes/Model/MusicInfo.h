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
public:
    static MusicInfo* initWithJson(string uuid);
    int getBeat();
    int getBpm();
    ValueVector getChords();
    ValueVector getLyircs();
    ValueVector getMusical();
    vector<string> getBluetoothChord();
    
    string getTitle();
    string getMusicFile();
    
};

#endif /* defined(__Guitar__MusicInfo__) */
