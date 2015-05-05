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
    //弦之间的宽度 （包括最上方的和弦标识信息）
    unitHeight = contentHeight/8;
    map<int,SectionInfo*> sections = musicModel->getSections();
    //小节拍数
    int beatFlag = musicModel->getBeatFlag();
    //小节总宽度
    sectionWidth = unitWidth*beatFlag;

    float sectionSize = (float)musicModel->getSections().size();
    musicTime =contentWidthTime+rhythmTime*sectionSize;

    //扫描音乐文件，找出和弦中的最小节拍，如果节拍过小，则显示会过于紧密，可将单元距离放大，速度加快(待补充）
    
};
