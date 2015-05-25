//
//  GameLevelSingleton.cpp
//  poputar
//
//  Created by allen on 15-4-12.
//
//

#include "POPTBaseDefine.h"

DECLARE_SINGLETON_MEMBER(GameLevelSingleton);
GameLevelSingleton::GameLevelSingleton(void){
    rapidjson::Document doc;
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile("config/gamelevel_config.json");
    doc.Parse<0>(jsonInfo.c_str());
    
    if(!doc.IsObject()){
        log("gamelevel_config.json is error!");
    }
    const rapidjson::Value &cArray = doc["levels"];
    
    for (int l=0; l<cArray.Size(); l++) {
        GameLevelInfo* gli = new GameLevelInfo();
        gli->setLevel(l+1);
        
        const rapidjson::Value &str = cArray[l];
        const rapidjson::Value &title = str["title"];
        const rapidjson::Value &cNodes = str["nodes"];
        gli->setTitle(title.GetString());
        
        vector<GameNodeInfo*> nodes;
        for(int n=0; n<cNodes.Size();n++){
            GameNodeInfo* gni = new GameNodeInfo();
            const rapidjson::Value &node = cNodes[n];
            const rapidjson::Value &cNode = node["node"];
            const rapidjson::Value &cMusic = node["music"];
            gni->setNode(cNode.GetInt());
            gni->setMusic(cMusic.GetString());
            gni->setGameLevelInfo(gli);
            
            nodes.push_back(gni);
        }
        
        gli->setNodes(nodes);
        levels.push_back(gli);
    }
}

GameLevelSingleton::~GameLevelSingleton(void){
    levels.clear();
}