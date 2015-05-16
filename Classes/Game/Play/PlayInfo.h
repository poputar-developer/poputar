//
//  PlayInfo.h
//  poputar
//
//  Created by allen on 15-5-14.
//
//

#ifndef __poputar__PlayInfo__
#define __poputar__PlayInfo__

#include <stdio.h>
#include <cocos-ext.h>
#include "PlayConfig.h"
USING_NS_CC;

class PlayInfo{
public:
    PlayConfig* config;
    
    float strToY(int str);
};
#endif /* defined(__poputar__PlayInfo__) */
