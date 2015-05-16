//
//  Section.h
//  poputar
//
//  Created by allen on 15-4-28.
//
//

#ifndef __poputar__Section__
#define __poputar__Section__

#include <stdio.h>
#include "PlayConfig.h"
#include <cocos-ext.h>
#include "PlayChord.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
using namespace std;

class Section : public Sprite{
public:
    
    ~Section();
    int sectionIndex;
    //和弦声音
    bool chordVoice;
    //主音声音
    bool toincVoice;
    //节拍器声音
    bool metronomeVoice;
    //品夹位置
    float capoValue;

    int minFlag = 4; //每拍拆分份数
    //小节类型，现存4种 ： 空、显示、试听、正式
    int type;
    
    //弹奏的和弦map 其中key为最小节拍的循环次数（从0开始）  例如： 一拍循环4次，其中第1次和第3次需要弹奏，则key为0，2
    Map<int,PlayChord*> playChords;
    
    Map<int, __String*> playTonics;
    
    PlayConfig* playConfig;
    
    string lastSection;
    //小节的总宽度
    float sectionWidth;
    
    string getChordFlag(string chordType);
    
    Color3B getChordColor(string chordType);
    
    
    /*
     创建小节  （配置信息、小节信息、y轴位置）
     */
    static Section *createSection(SectionInfo* sectionInfo,int index,int type);
    
    void loadRhythm();
    void loadMusical(SectionInfo* sectionInfo);
    
    void createHeadChord(string chordType,Vec2 position, Size preferredSize);
    
    ActionInterval* move(int count);
    
    bool updateState(float relativePosX,int type);
    
    void sendBlueTooth4Chord(PlayChord *chord);
    
    void sendBlueTooth4Beat(PlayChord *chord);
    
    //和弦声音控制
    void chordVoiceCallback(Ref* ref);
    //节拍器声音控制
    void metronomeVoiceCallback(Ref* ref);
    //主音控制
    void toincVoiceCallBack(Ref* ref);
    //品夹控制 升降调
    void capoChangeCallback(Ref* ref);
    
};

#endif /* defined(__poputar__Section__) */
