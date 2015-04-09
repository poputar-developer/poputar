//
//  MusicController.h
//  poputar
//
//  Created by allen on 15-4-7.
//
//

#ifndef __poputar__MusicController__
#define __poputar__MusicController__

#include <cocos-ext.h>
#include <stdio.h>
#include "extensions/GUI/CCControlExtension/CCControlSwitch.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"
USING_NS_CC;

using namespace std;
using namespace cocos2d::extension;
class MusicMenuDelegate{
public:
    virtual void speedChangeCallback(float speedBase)=0;
    virtual void metronomePlayCallback(bool isOn)=0;
    virtual void musicalPlayCallback(bool isOn)=0;
};

class MusicMenu : public ui::Scale9Sprite{
private:
    float speedBase;
    MusicMenuDelegate* _delegate;
    void loadFrame();
public:
    static MusicMenu* createMusicMenu();
    
    void setDelegate(MusicMenuDelegate * delegate);
    
    void speedChangeController(Ref *ref,bool isSpeedUp,Label* speedFlagLabel);
    void metronomePlayController(Ref *ref,Control::EventType type);
    void musicalPlayController(Ref *ref,Control::EventType type);
};

#endif /* defined(__poputar__MusicController__) */
