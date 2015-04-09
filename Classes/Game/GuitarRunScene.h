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
#include "MusicMenu.h"
#include "GameMenu.h"
#include "MusicMenu.h"
USING_NS_CC;
using namespace cocos2d::extension;


class GuitarRun: public Layer,public GameMenuDelegate,public MusicMenuDelegate{
  
private:
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    RunLayer *runLayer;
    //当前速度基数 用于加减速控制
    float speedBase;
    //是否已经暂停 用于暂停按钮控制
    bool isPause;
    
    bool musicMenuDisplay;
    
    float time_now;
    
    POPTSlider* slider;
    //组装界面
    void initialise();
    
    void loadTopFrame(MusicInfo* musicInfo,float height);
    
    void loadFootFrame(float height);
    
    //开始和弦弹奏
    void startChordMusic(MusicInfo *musicInfo,float proportion);
    //开始指弹
    void startFingerMusic(MusicInfo *musicInfo,float proportion);
    //暂停控制
    void pauseControll(Ref* ref,bool flag);
    //音乐控制
    void musicControll(Ref* ref,MusicMenu* mm);
    //主菜单控制
    void menuControll(Ref* ref);
    //移动节奏界面
    void moveMusicMenu(bool moveIn,MusicMenu* mm);
    
    
    //开始动画
    void startAnimation();
    //时间轴移动
    void moveSlider(float at);
    //时间轴值发生改变
    void sliderChanged(Ref *ref,Control::EventType controllEvent);
    
    //菜单控制代理
    virtual void goOnCallback(Ref* ref);
    virtual void restartCallback(Ref* ref);
    virtual void goBackCallback(Ref* ref);
    
    //音乐控制
    virtual void speedChangeCallback(float speedBase);
    virtual void metronomePlayCallback(bool isOn);
    virtual void musicalPlayCallback(bool isOn);
public:
    static Scene *createScene(MusicInfo *musicInfo,GameInfo *gameInfo);

    CREATE_FUNC(GuitarRun);

    virtual void setBackground();
    
    virtual void goBack(Ref* sender);
};




#endif /* defined(__Guitar__GuitarRunScene__) */
