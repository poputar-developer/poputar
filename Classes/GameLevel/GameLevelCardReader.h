//
//  GameLevelCardReader.h
//  poputar
//
//  Created by allen on 15-5-9.
//
//

#ifndef __poputar__GameLevelCardReader__
#define __poputar__GameLevelCardReader__

#include "cocos2d.h"
#include "cocostudio/CocosStudioExport.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class GameLevelCardReader : public  cocostudio::NodeReader{
public:
    GameLevelCardReader(){};
    ~GameLevelCardReader(){};
    static GameLevelCardReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__poputar__GameLevelCardReader__) */
