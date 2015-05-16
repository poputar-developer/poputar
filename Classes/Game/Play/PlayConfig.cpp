//
//  FingerConfig.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "PlayConfig.h"

PlayConfig::PlayConfig(float contentWidth, float contentHeight, MusicModel *musicModel):GameConfig::GameConfig(contentWidth,contentHeight){
    
    //循环周期
    this->musicModel = musicModel;
    int bpm = musicModel->getBpm();
    //单位时间 每一拍的时间
    unitTime = 60.0/bpm;
    //小节循环周期 = 单位时间*小节拍数
    rhythmTime = unitTime*musicModel->getBeatFlag();
    
    //从右侧到撞击线的距离
    rhythmWidth= contentWidth- impactLine;
    //计算每秒移动距离
    move4sec = unitWidth/unitTime;
    //从生成到移动到撞击线所需时间
    allTime = rhythmWidth/move4sec;
    //整个界面的时间
    contentWidthTime = contentWidth/move4sec;
    //和弦展示区域高度
    chordHeight = contentHeight/8;
    //弦的区域高度
    stringsHeight = contentHeight-chordHeight-stringSideHeight*2;
    //弦之间的距离
    stringUnitHeight = stringsHeight/5;
    map<int,SectionInfo*> sections = musicModel->getSections();
    //小节拍数
    int beatFlag = musicModel->getBeatFlag();
    //小节总宽度
    sectionWidth = unitWidth*beatFlag;

    map<int,MusicPlayInfo*> plays =  musicModel->getPlayInfo();
    int sectionSize=0;
    for (int p=1; p<plays.size()+1; p++) {
        MusicPlayInfo* playInfo = plays[p];
        int startIndex = playInfo->startSection;
        int endIndex = playInfo->endSection;
        sectionSize+=(endIndex-startIndex)+1;
    }
//    float sectionSize = (float)musicModel->getSections().size();
    musicTime =contentWidthTime+rhythmTime*(float)sectionSize;

    
    //1、根据每秒移动距离计算开始动画的移动距离
    float countdownWidth = move4sec * 4.0f;
    //2、根据开始动画距离和到整个画面计算前置小节个数
    float beforWidth = contentWidth+countdownWidth;
    beforSectionSize =  (int)(beforWidth/sectionWidth);
    if((int)beforWidth%(int)sectionWidth>0){
        beforSectionSize+=1;
    }
    //3、计算开始小节的宽度
    float beforSectionWidth = sectionWidth*beforSectionSize;
    //4、根据总宽度计算层的的起始位置
    startX = beforSectionWidth-beforWidth;

    //1、根据每秒移动距离计算结尾移动距离
    float endWidth = move4sec * endTime;
    //2、根据画面距离和结尾距离计算和弦个数
    float afterWidth = contentWidth+endWidth;
    afterSectionSize = (int)(afterWidth/sectionWidth);
    if((int)afterWidth%(int)sectionWidth>0){
        afterSectionSize+=1;
    }
    
    //扫描音乐文件，找出和弦中的最小节拍，如果节拍过小，则显示会过于紧密，可将单元距离放大，速度加快(待补充）
    
};
