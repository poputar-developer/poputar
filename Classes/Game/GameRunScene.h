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
#include "EndLayer.h"
#include "AuditionLayer.h"
#include "cocostudio/CocoStudio.h"
#include "PlayRunLayer.h"
#include "Lyric.h"
USING_NS_CC;
using namespace cocostudio::timeline;
using namespace cocos2d::extension;

class GuitarRun: public Layer,public EndLayerDelegate,public AuditionLayerDelegate,public PlayRunLayerDelegate{
  
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
    //歌词信息
    
    //当前歌词标识
    int currLyricflag = 3;
    //歌词标识（用来区分当前更新的时第几句歌词）
    bool lyricFlag;
    //歌词实例
    Lyric* lyric1;
    Lyric* lyric2;
    
    map<int,Lyric*> lyricMap;
    
    //组装界面
    void initVoice();
    
    void initParam();
    
    void loadGameFrame();
    
    void loadTopFrame();
    
    void loadFootFrame();
    
    void loadLyric();
    
    //开始弹奏页面
    PlayRunLayer* startFingerMusic(MusicModel *musicModel,float proportion);
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
    //游戏结束
    void gameEnd();
    
    //结束页面的回调
    virtual void endRestartCallback();
    virtual void endNextCallback(bool isPassLevel);
    virtual void endBackCallback(bool isPassLevel);
    
    virtual void auditionBackCallback(Ref *ref);
    
    virtual void lyricCallback(int p,int s,int t);
    
    void passLevel();
    
public:
    static Scene *createScene();

    CREATE_FUNC(GuitarRun);

    virtual void setBackground();
    
    virtual void goBack(Ref* sender);
    
    
    void clearModel();
    
    
};

#endif /* defined(__Guitar__GuitarRunScene__) */
