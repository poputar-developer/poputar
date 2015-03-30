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
#include "Common.h"
#include "POPTHelper.h"
#include "MusicInfo.h"

USING_NS_CC;
class RunLayer : public LayerColor{
public:
    //公告属性
    Common *common;
    //画面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();

    virtual bool init(const Color4B &color,MusicInfo *musicInfo);
    
    //开始动画
    void startAnimation();
    
    //发送蓝牙数据
    virtual void sendDataToBluetooth(){};
    
    //返回时清空当前播放的参数
    virtual void stopMusic(){};
    
    //动画结束后设置属性
    virtual void endAnimationSetting(){};
    
};

#endif /* defined(__poputar__RunLayer__) */
