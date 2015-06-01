//
//  StartLayer.h
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#ifndef __poputar__StartLayer__
#define __poputar__StartLayer__

#include <stdio.h>
#include "../../Base/POPTVideoPlayer.h"
USING_NS_CC;
class StartScene:public Layer{
    
private:
    
    ui::Button *skipBtn;
    bool isPlaying;
    
    POPTVideoPlayer* videoPlayer;
    
    void loadFrame();
    
    void skipController(Ref* ref);
    
    void replayController(Ref* ref);
    
    void videoPauseController(Ref* ref);
    
//    void studyController(Ref* ref);
public:
    static Scene* createScene();
    
    static StartScene* createStartScene();
    
    void videoPlayOverCallback();
    
    void showVideo();
    
    virtual void setBackground();
    
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void videoEventCallback(Ref* sender,cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif
    
};

#endif /* defined(__poputar__StartLayer__) */
