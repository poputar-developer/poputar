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
//#include "Common.h"
#include "FingerConfig.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class Musical : public Sprite{
private:
    //所在弦
    int key;
    //所在品
    int value;
    //弦的具体位置
    float y;
    //文字信息
    Label *label;
    
    std::string fileName;
    
public:
    //是否已经发生碰撞
    bool isCollision=false;
    //所属小节
    int beat;
    
    static Musical *createMusical(int key,int value,float y);
    void loadFrame();
    
    ActionInterval* musicalMove(FingerConfig *common);
    
    ActionInterval* musicalFadeOut(FingerConfig *common,bool isLabel);
    
    void runLeftAction(FingerConfig *config);
    
    void musicalVoice();
};

#endif /* defined(__poputar__Musical__) */
