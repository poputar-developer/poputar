//
//  GuitarRunScene.h
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__GuitarRunScene__
#define __Guitar__GuitarRunScene__

#include <stdio.h>
#include "cocos2d.h"
#include <MusicInfo.h>
#include "BaseLayer.h"
#include "GameInfo.h"

#include "RunLayer.h"
#include <cocos-ext.h>
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "POPTSlider.h"
USING_NS_CC;
using namespace cocos2d::extension;

class GuitarRun: public BaseLayer{
  

private:
    RunLayer *runLayer;
    //当前速度基数 用于加减速控制
    float speedBase;
    //是否已经暂停 用于暂停按钮控制
    bool isPause;
    
    float time_now;
    
    POPTSlider* slider;
    //组装界面
    void loadFrame(MusicInfo* musicInfo);
    //开始和弦弹奏
    void startChordMusic(MusicInfo *musicInfo);
    //开始指弹
    void startFingerMusic(MusicInfo *musicInfo);
    //速度控制
    void speedControll(Ref* ref,bool flag);
    //暂停控制
    void pauseControll(Ref* ref,bool flag);
    
    //开始动画
    void startAnimation();
    
    void moveSlider(float at);
    
    void sliderChanged(Ref *ref,Control::EventType controllEvent);
    
public:
    static Scene *createScene(MusicInfo *musicInfo,GameInfo *gameInfo);

    CREATE_FUNC(GuitarRun);

    virtual void setBackground();
    
    virtual void goBack(Ref* sender);
};




#endif /* defined(__Guitar__GuitarRunScene__) */
