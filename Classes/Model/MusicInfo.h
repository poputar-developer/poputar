//
//  MusicInfo.h
//  Guitar
//
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
    

    
public:
    static MusicInfo* initWithJson(string uuid);
    int getBeat();
    int getBpm();
    ValueVector getChords();
    ValueVector getLyircs();
    vector<string> getBluetoothChord();
};

#endif /* defined(__Guitar__MusicInfo__) */
