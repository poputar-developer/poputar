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
#include "Common.h"
USING_NS_CC;

class Musical : public Sprite{
private:
    //所在弦
    int key;
    //所在品
    int value;
    //弦的具体位置
    float y;
public:
    static Musical *createMusical(std::string filename,int key,int value,float y);
    
    ActionInterval* musicalMove(Common *common,int speed);
    
    ActionInterval* musicalFadeOut(Common *common);
    
    void musicalVoice();
};

#endif /* defined(__poputar__Musical__) */
