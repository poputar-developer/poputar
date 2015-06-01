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
#include "cocostudio/CocoStudio.h"
#include "./End/EndLayer.h"
#include "./Audition/AuditionLayer.h"
#include "./Play/PlayRunLayer.h"
#include "./Play/Lyric.h"

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
    //当前歌词标识
    int currLyricflag;
    //歌词标识（用来区分当前更新的时第几句歌词）
    bool lyricFlag;
    //上下两段歌词实例
    Lyric* lyric1;
    Lyric* lyric2;
    //所有歌词的实例容器
    map<int,Lyric*> lyricMap;
    //初始化声音
    void initVoice();
    //初始化参数
    void initParam();
    //加载游戏界面
    void loadGameFrame();
    //加载头部控制区域
    void loadTopFrame();
    //加载底部控制区域
    void loadFootFrame();
    //加载歌词信息
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
    //返回公共方法
    void goBack();
    //重新开始公共方法
    void restart();
    //结束页面的回调
    virtual void endRestartCallback();
    virtual void endNextCallback(bool isPassLevel);
    virtual void endBackCallback(bool isPassLevel);
    //游戏中的退出和重新开始
    void playingBack(Ref* sender);
    void playingRestart(Ref* sender);
    //退出试听回调方法
    virtual void auditionBackCallback(Ref *ref);
    //歌词进度回调方法
    virtual void lyricCallback(int p,int s,int t);
    //通过阶段跳转
    void passLevel();
    
public:
    static Scene *createScene();

    CREATE_FUNC(GuitarRun);
    //设置背景
    virtual void setBackground();
    //清空模型信息
    void clearModel();
};

#endif /* defined(__Guitar__GuitarRunScene__) */
