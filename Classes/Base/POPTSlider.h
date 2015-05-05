//
//  Slider.h
//  poputar
//
//  Created by allen on 15-4-6.
//
//

#ifndef __poputar__Slider__
#define __poputar__Slider__
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"
#include <stdio.h>
#include "RunLayer.h"
USING_NS_CC;
class POPTSliderDelegate{
public:
    virtual void sliderMoveEnd()=0;
    virtual void sliderTouchEndCallback()=0;
};

using namespace cocos2d::extension;
class POPTSlider:public ControlSlider{
private:
    POPTSliderDelegate* _delegate;
    bool drag;
    bool moving;
    float moveTime=0.01f;
protected:
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    virtual bool onTouchBegan(Touch* touch, Event* pEvent);
    virtual void sliderMove(float dt);
public:
    void loadTimeInfo();
    int musicalIndex;
    //创建时间轴 背景文件，前进文件，移动标识，是否可以拖动标识
    static POPTSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile,bool drag);
    void setDelegate(POPTSliderDelegate* delegate);
    void startSliderMove(bool flag);
    void sliderPasue(bool flag);
   
};

#endif /* defined(__poputar__Slider__) */
