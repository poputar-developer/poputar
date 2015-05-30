//
//  PassSence.h
//  poputar
//
//  Created by allen on 15-5-30.
//
//

#ifndef __poputar__PassSence__
#define __poputar__PassSence__

#include <stdio.h>

USING_NS_CC;
class PassSence:public Layer{
    
private:
    //默认帧数 与cocos studio中动画需要一致
    int defaultFrame=60;
    
    Node* pickNode;
public:
    static Scene *createScene();
    CREATE_FUNC(PassSence);
    
    virtual bool init();
    
    void startPickAction(int level);
    
    void goOnController(Ref* ref);
};

#endif /* defined(__poputar__PassSence__) */
