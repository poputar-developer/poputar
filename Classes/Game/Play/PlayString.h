//
//  PlayString.h
//  poputar
//
//  Created by allen on 15-5-14.
//
//

#ifndef __poputar__PlayString__
#define __poputar__PlayString__

#include <stdio.h>
#include "PlayInfo.h"
using namespace std;
class PlayString:public Sprite,public PlayInfo{
public:
    
    float x;
    
    static PlayString* createPlayString(string strInfo,string cop,string circleFileName,float x);
    
    void loadFrame(string strInfo,string cop,string circleFileName);
};

#endif /* defined(__poputar__PlayString__) */
