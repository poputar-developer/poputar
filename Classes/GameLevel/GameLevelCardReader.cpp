//
//  GameLevelCardReader.cpp
//  poputar
//
//  Created by allen on 15-5-9.
//
//

#include "POPTBaseDefine.h"

USING_NS_CC;

static GameLevelCardReader* _instance = nullptr;

GameLevelCardReader* GameLevelCardReader::getInstance(){
    if(!_instance){
        _instance = new GameLevelCardReader();
    }
    return _instance;
}

void GameLevelCardReader::purge(){
    CC_SAFE_DELETE(_instance);
}

Node* GameLevelCardReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions){
    GameLevelCardHandler* node = GameLevelCardHandler::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
