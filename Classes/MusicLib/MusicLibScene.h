
//
//  MusicLibScene.h
//  poputar
//
//  Created by allen on 15-6-3.
//
//

#ifndef __poputar__MusicLibScene__
#define __poputar__MusicLibScene__

#include <stdio.h>
USING_NS_CC;

class MusicLibScene :public Layer{
public:
    static Scene* createScene();
    
    CREATE_FUNC(MusicLibScene);
    
    virtual bool init();
    
    void backBtnController(Ref* ref);
};

#endif /* defined(__poputar__MusicLibScene__) */
