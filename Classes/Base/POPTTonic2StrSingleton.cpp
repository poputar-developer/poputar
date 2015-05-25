//
//  POPTTonic2Str.cpp
//  poputar
//
//  Created by allen on 15-5-20.
//
//
#include "POPTBaseDefine.h"

DECLARE_SINGLETON_MEMBER(POPTTonic2StrSingleton);

POPTTonic2StrSingleton::POPTTonic2StrSingleton(){
    
}

POPTTonic2StrSingleton::~POPTTonic2StrSingleton(){
    
}

void POPTTonic2StrSingleton::loadCurrentTonic(string type){
    rapidjson::Document doc;
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile("config/"+type+"_str.json");
    doc.Parse<0>(jsonInfo.c_str());

    const rapidjson::Value &cArray = doc["tonicStr"];
    
    for (int t=0; t<cArray.Size(); t++) {

        const rapidjson::Value &tonicArray = cArray[t];
        const rapidjson::Value &tonic = tonicArray["tonic"];
        const rapidjson::Value &str = tonicArray["str"];
        tonic2StrMap[tonic.GetString()] = str.GetString();
    }
}

void POPTTonic2StrSingleton::unLoadTonic(){
    tonic2StrMap.clear();
}

string POPTTonic2StrSingleton::getStrInfo(string note){
    return tonic2StrMap[note];
}