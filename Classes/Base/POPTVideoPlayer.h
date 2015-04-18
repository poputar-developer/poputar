//
//  POPTVideoPlayer.h
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#ifndef __poputar__POPTVideoPlayer__
#define __poputar__POPTVideoPlayer__

#include <stdio.h>
#include "ui/UIVideoPlayer.h"
class POPTVideoPlayer:public cocos2d::experimental::ui::VideoPlayer{
public:
    
    POPTVideoPlayer();
    virtual void setFileName(const std::string& videoPath);
    
    CREATE_FUNC(POPTVideoPlayer);
};

#endif /* defined(__poputar__POPTVideoPlayer__) */
