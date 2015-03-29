//
//  Lyric.h
//  Guitars
//
//  Created by allen on 14-12-4.
//
//

#ifndef __Guitars__Lyric__
#define __Guitars__Lyric__

#include <stdio.h>
USING_NS_CC;
using namespace std;

class Lyric : public Sprite {
    
public:
    virtual bool init();
    CREATE_FUNC(Lyric);
    void setLyircStr(string lyric);
    
};
#endif /* defined(__Guitars__Lyric__) */
