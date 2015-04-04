//
//  Musical.h
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#ifndef __poputar__Musical__
#define __poputar__Musical__

#include <stdio.h>
#include <cocos-ext.h>
#include "FingerConfig.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class Musical : public ui::Scale9Sprite{
private:
    //所在弦
    int key;
    //所在品
    int value;
    //用来进行移动的时候保持平行 始终等于unitHeight
    float y;
    //弦的位置
    ValueMapIntKey stringMap;
    //声音文件
    ValueVector voiceFileName;
    
    string content;
    
    ValueVector stringsInfo;
    
public:
    //是否已经发生碰撞
    bool isCollision=false;

    
    static Musical *createMusical(FingerConfig* config ,string content,float unitHeight);
    void loadMusical(string content,float unitHeight);
    
    ActionInterval* musicalMove(FingerConfig *common);
    
    void musicalVoice();
    
    string getContent();
    
    ValueVector getStringsInfo();
};

#endif /* defined(__poputar__Musical__) */
