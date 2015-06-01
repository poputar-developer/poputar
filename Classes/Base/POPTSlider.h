//
//  Slider.h
//  poputar
//  时间轴
//  Created by allen on 15-4-6.
//
//

#ifndef __poputar__Slider__
#define __poputar__Slider__
#include "extensions/GUI/CCControlExtension/CCControlSlider.h"
#include <stdio.h>

USING_NS_CC;
//时间轴代理类
class POPTSliderDelegate{
public:
    //松开时间轴后的回调方法
    virtual void sliderTouchEndCallback(Ref* ref)=0;
};

using namespace cocos2d::extension;
class POPTSlider:public ControlSlider{
private:
    //时间轴代理类
    POPTSliderDelegate* _delegate;
protected:
    //拖动结束方法
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
public:
    //创建时间轴
    static POPTSlider* create(const char* bgFile, const char* progressFile, const char* thumbFile);
    //设置代理类
    void setDelegate(POPTSliderDelegate* delegate);
   
};

#endif /* defined(__poputar__Slider__) */
