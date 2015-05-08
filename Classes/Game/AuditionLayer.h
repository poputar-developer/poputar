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
#include "GameMenu.h"
#include "POPTSlider.h"

class AuditionLayer : public MenuBaseLayer,public POPTSliderDelegate{
private:
public:
    
    static AuditionLayer* createAuditionLayer(float nowTime);
    
    bool init();
    
    void loadFrame(float nowTime);

    
    bool onTouchBegan(Touch* touch,Event* event);
    void onTouchMoved(Touch* touch,Event* event);
    void onTouchEnded(Touch* touch,Event* event);
    
    virtual void sliderMoveEnd(Ref* ref);
    virtual void sliderTouchEndCallback(Ref* ref);
};

#endif /* defined(__poputar__AuditionLayer__) */
