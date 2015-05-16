//
//  RunLayer.h
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#ifndef __poputar__RunLayer__
#define __poputar__RunLayer__

#include <stdio.h>
//#include "Common.h"
#include "POPTHelper.h"
#include "MusicInfo.h"
#include "MusicModel.h"
#include "GameConfig.h"

USING_NS_CC;
class RunLayer : public LayerColor{
protected:
public:
    ~RunLayer();
    

    //公告属性
    GameConfig *gameConfig;
    //初始化
    virtual bool init(const Color4B &color);
    
    //发送蓝牙数据
    virtual void sendDataToBluetooth(){};
    //返回时清空当前播放的参数
    virtual void stopMusic(){};
    //动画结束后设置属性
    virtual void endAnimationSetting(){};
    //从index重新开始
    virtual void restart(int musicalIndex){};
    
    //根据传入音符计算时间
    virtual float getMusicalTime(int musicalIndex){return 0.0f;};
    //根据传入音符所在小节
    virtual string getMusicalChord(int musicalIndex){return nullptr;};
    //是否试听
    virtual void audition(bool isAudition){};
    //试听位置
    virtual void auditionResume(Ref* ref){};
    virtual void auditionPause(Ref* ref){};
    
    virtual void sectionPause(){};
    
    virtual void sectionResume(){};
    

};

#endif /* defined(__poputar__RunLayer__) */
