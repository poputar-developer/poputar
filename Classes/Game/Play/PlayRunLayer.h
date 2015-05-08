//
//  FingerRunLayer.h
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#ifndef __poputar__PlayRunLayer__
#define __poputar__PlayRunLayer__

#include <stdio.h>
#include <cocos-ext.h>
#include "RunLayer.h"
#include "PlayConfig.h"
#include "SimpleAudioEngine.h"
#include "Section.h"

USING_NS_CC;
using namespace std;


class PlayRunLayer : public RunLayer{


private:
    
    //配置信息
    PlayConfig *playConfig;
    //组装画面
    void loadFrame();
    //初始化开始的音符
    void startMusical(int musicalIndex);
    //碰撞检测
    void update(float at);
    //通知小节
    void sectionNotice(int type);
    //得到运动动作
    ActionInterval* getMoveActionIterval();
    
    //新建音符时用于设置音符当前的tag
    int currentMusical;
    ValueMapIntKey stringMap;
    //获取准备播放的音符
    int flag;
    //是否试听
    bool isAudition;
    //音乐信息中获取的音符信息
    ValueVector musicals;
    //节奏线集合
    Vector<Sprite *> rhythms;
    
    Layer *sectionLayer;
    Layer *testSectionLayer;
    //播放时小节信息
    Map<int,Section*> sectionSprite;
    //试听时小节信息
    Map<int,Section*> auditionSprite;
    
    virtual void sectionPause();
    
    virtual void sectionResume();
    
public:
    bool init4Finger(const Color4B &&color,MusicModel *musicModel,float proportion);
    static PlayRunLayer *createPlayRunLayer(MusicModel *musicModel,float proportion);
    virtual void stopMusic();
    virtual void endAnimationSetting();
    virtual void sendDataToBluetooth();
    virtual void restart(int musicalIndex);
    virtual float getMusicalTime(int musicalIndex);
    virtual string getMusicalChord(int musicalIndex);
    virtual void audition(bool isAudition);
    
    void auditionControll(int type);
    
    virtual void auditionSilderPos(Ref* ref);
    
};
#endif /* defined(__poputar__PlayRunLayer__) */
