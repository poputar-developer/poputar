//
//  GuitarRunScene.h
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#ifndef __Guitar__GameRunScene__
#define __Guitar__GameRunScene__

#include <stdio.h>
#include "cocos2d.h"
//#include "BaseLayer.h"
//#include "GameInfo.h"
#include "POPTBaseDefine.h"
#include "RunLayer.h"
//#include <cocos-ext.h>
//#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "EndLayer.h"
#include "GameLevelSingleton.h"
#include "MusicModel.h"
#include "AuditionLayer.h"
#include"cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::extension;


class GuitarRun: public Layer,public EndLayerDelegate,public AuditionLayerDelegate{
  
private:
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //头部高度
    float topSideHeight = 82.0f;
    float footSideHeight= 90.0f;
    //暂停按钮
    ui::Button* pauseBtn;
    //重新开始按钮
    ui::Button* restartBtn;
    //是否已经暂停 用于暂停按钮控制
    bool isPause;
    //当前时间
    float time_now;
    //时间信息
    Label* time;
    //组装界面
    void initialise();
    
    void loadGameFrame();
    
    void loadTopFrame();
    
    void loadFootFrame();
    
    //开始弹奏页面
    RunLayer* startFingerMusic(MusicModel *musicModel,float proportion);
    //暂停控制
    void pauseControll(Ref* ref);
    //试听按钮功能
    void auditionControll(Ref* ref);
    //暂停
    void pauseGame();
    //继续
    void resumeGame();
    
    //开始动画
    void startAnimation();
    //时间轴移动
    void moveTime(float at);
    
    //结束页面的回调
    virtual void endRestartCallback();
    virtual void endNextCallback();
    virtual void endBackCallback();
    
    virtual void auditionBackCallback(Ref *ref);
public:
    static Scene *createScene();

    CREATE_FUNC(GuitarRun);

    virtual void setBackground();
    
    virtual void goBack(Ref* sender);
    
    
};

#endif /* defined(__Guitar__GuitarRunScene__) */
