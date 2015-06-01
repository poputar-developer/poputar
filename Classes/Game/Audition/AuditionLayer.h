//
//  AuditionLayer.h
//  poputar
//
//  Created by allen on 15-5-5.
//
//

#ifndef __poputar__AuditionLayer__
#define __poputar__AuditionLayer__

#include <stdio.h>
#include "../../Base/POPTSlider.h"
#include "../../Base/MaskBaseLayer.h"
#include <cocos-ext.h>

USING_NS_CC;
USING_NS_CC_EXT;

class AuditionLayerDelegate{
public:
    virtual void auditionBackCallback(Ref* ref)=0;
};

class AuditionLayer : public MaskBaseLayer,public POPTSliderDelegate{
private:
    string title;
    float nowTime;
    float allTime;
    
    bool isPause;
    POPTSlider* slider;
    ui::Button* pauseBtn;
    Label* nowTimeLabel;
public:
    AuditionLayerDelegate* _delegate;
    
    static AuditionLayer* createAuditionLayer(string title,float startTime,float allTime);
    
    void loadFrame();
    //暂停控制
    void pauseControll(Ref* ref);
    void pauseAudition();
    void resumeAudition();
    //重新开始控制
    void restartControll(Ref* ref);
    //定时任务
    void moveTime(float at);
    
    void sliderChanged(Ref *ref,Control::EventType controllEvent);
    virtual void sliderTouchEndCallback(Ref* ref);
    
    void setDelegate(AuditionLayerDelegate* delegate);
};

#endif /* defined(__poputar__AuditionLayer__) */
