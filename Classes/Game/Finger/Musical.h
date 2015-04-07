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
    //用来进行移动的时候保持平行 始终等于unitHeight
    float y;
    //声音文件
    ValueVector voiceFileName;
    //音符内容
    string content;
    //当前音符所使用的弦
    ValueVector stringsInfo;
    
public:
    //是否已经发生碰撞
    bool isCollision=false;

    static Musical *createMusical(FingerConfig* config ,string content,float unitHeight);
    
    static Musical *createMusical(FingerConfig* config ,string content,float unitHeight,float x);

    void loadMusical(string content,float unitHeight);
    
    //移动节奏线方法，第二个参数是用于倒计时创建的节奏线不是从屏幕最右侧建立，计算需要移动的记录时使用
    ActionInterval* musicalMove(FingerConfig *common,float unitWidth);
    
    void musicalVoice();
    
    string getContent();
    
    ValueVector getStringsInfo();
};

#endif /* defined(__poputar__Musical__) */
