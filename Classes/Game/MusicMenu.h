//
//  MusicController.h
//  poputar
//
//  Created by allen on 15-4-7.
//
//

#ifndef __poputar__MusicMenu__
#define __poputar__MusicMenu__

#include <cocos-ext.h>
#include <stdio.h>
#include "extensions/GUI/CCControlExtension/CCControlSwitch.h"
#include "extensions/GUI/CCControlExtension/CCControl.h"
#include "POPTBaseDefine.h"
USING_NS_CC;

using namespace std;
using namespace cocos2d::extension;
class MusicMenu : public ui::Scale9Sprite{
private:
    float speedBase;
    float capoBase;
    int capoValue;
    void loadFrame();
public:
    static MusicMenu* createMusicMenu();
    void speedChangeController(Ref *ref,bool isSpeedUp,Label* speedFlagLabel);
    void capoChangeController(Ref* ref,bool isCapoUp,Label* capoFlagLabel);
    void metronomePlayController(Ref *ref,Control::EventType type);
    void musicalPlayController(Ref *ref,Control::EventType type);
};

#endif /* defined(__poputar__MusicMenu__) */
