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
USING_NS_CC;

class MusicMenu : public ui::Scale9Sprite{
private:
    void loadFrame();
public:
    static MusicMenu* createMusicMenu();
};

#endif /* defined(__poputar__MusicController__) */
