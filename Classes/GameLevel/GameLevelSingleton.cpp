//
//  GameLevelSingleton.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "GameLevelSingleton.h"

GameLevelSingleton * GameLevelSingleton::instance = NULL;
GameLevelSingleton* GameLevelSingleton::getInstance(){
    if(!instance){
        instance = new GameLevelSingleton();
        instance->init();
    }
    return instance;
}

void GameLevelSingleton::init(){
    rapidjson::Document doc;
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile("gamelevel_config.json");
    doc.Parse<0>(jsonInfo.c_str());
    
    if(!doc.IsObject()){
        log("gamelevel_config.json is error!");
    }
    const rapidjson::Value &cArray = doc["levels"];
    
    //计算页面高度
    for (int l=0; l<cArray.Size(); l++) {
        GameLevelInfo* gli = new GameLevelInfo();
        gli->setLevel(l+1);
        
        const rapidjson::Value &str = cArray[l];
        const rapidjson::Value &cNodes = str["nodes"];
        
        vector<GameNodeInfo*> nodes;
        for(int n=0; n<cNodes.Size();n++){
            GameNodeInfo* gni = new GameNodeInfo();
            const rapidjson::Value &node = cNodes[n];
            const rapidjson::Value &cNode = node["node"];
            const rapidjson::Value &cType = node["type"];
            const rapidjson::Value &cMusic = node["music"];
            gni->setNode(cNode.GetInt());
            gni->setType(cType.GetString());
            gni->setMusic(cMusic.GetString());
            gni->setGameLevelInfo(gli);
            //加载音乐信息
            auto musicInfo = MusicInfo::initWithJson(cMusic.GetString());
            gni->setMusicInfo(musicInfo);
            
            nodes.push_back(gni);
        }
        
        gli->setNodes(nodes);
        levels.push_back(gli);
    }
}

vector<GameLevelInfo*> GameLevelSingleton::getLeves(){
    return levels;
}