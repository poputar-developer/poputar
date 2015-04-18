//
//  POPTVideoPlayer.cpp
//  poputar
//
//  Created by allen on 15-4-13.
//
//
#include "UIVideoPlayer.h"
#include "POPTVideoPlayer.h"
#include "UIVideoPlayer-ios.mm"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
using namespace cocos2d::experimental::ui;

@interface POPTUIVideoViewWrapperIos:UIVideoViewWrapperIos
- (void) setURL:(int) videoSource :(std::string&) videoUrl;
@end

@implementation POPTUIVideoViewWrapperIos
{
}

- (void) setURL:(int) videoSource :(std::string&) videoUrl{
    [super setURL:videoSource :videoUrl];
    super.moviePlayer.controlStyle = MPMovieControlStyleNone;
}
@end


POPTVideoPlayer::POPTVideoPlayer()
{
    _videoView = [[POPTUIVideoViewWrapperIos alloc] init:this];
    
#if CC_VIDEOPLAYER_DEBUG_DRAW
    _debugDrawNode = DrawNode::create();
    addChild(_debugDrawNode);
#endif
}


void POPTVideoPlayer::setFileName(const std::string& fileName)
{
    _videoURL = fileName;
    _videoSource = VideoPlayer::Source::FILENAME;
    
    POPTUIVideoViewWrapperIos* pptvvwi = (POPTUIVideoViewWrapperIos*)_videoView;
    [pptvvwi setURL:(int)_videoSource :_videoURL];
    //[((POPTUIVideoViewWrapperIos*)_videoView) setURL:(int)_videoSource :_videoURL];
}


#endif
