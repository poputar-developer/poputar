//
//  ChordAnalysis.cpp
//  poputar
//
//  Created by allen on 15-3-27.
//
//
#include "../Base/POPTBaseDefine.h"

DECLARE_SINGLETON_MEMBER(MusicAnalysis);
map<string,string> chordInfo;

MusicAnalysis::MusicAnalysis(void){
    
    //读取和弦对应关系文件
    rapidjson::Document doc;
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile("config/chordInfo.json");
    
    doc.Parse<0>(jsonInfo.c_str());
    
    if(!doc.IsObject()){
        log("chordInfo.json is error!");
    }

    const rapidjson::Value &cArray = doc["chords"];
    if(!cArray.IsArray()){
        log("chords array is error!");
    }
    
    for(rapidjson::SizeType i=0;i<cArray.Size();i++){
        const rapidjson::Value &str = cArray[i];
        const rapidjson::Value &cType = str["type"];
        const rapidjson::Value &cData = str["data"];
        
        string type =cType.GetString();
        string data = cData.GetString();
        
        chordInfo.insert(pair<string, string>(type,data));
    }
    
}

void MusicAnalysis::sendChordStr(string chord){
    map<string,string>::iterator it;
    it = chordInfo.find(chord);
    
    if(it != chordInfo.end()){
        this->sendMusicChar(chordInfo[chord]);
    }
}

void MusicAnalysis::sendMusicChar(string musical){
    vector<string> infos = POPTStringUtils::split(musical, "@|@");
    map<int,int> charInfo;
    
    for(size_t i=0;i<infos.size();i++){
        string info = infos[i];
        if(info.length()>0){
            vector<string> s = POPTStringUtils::split(info, ":");
            int key = atoi(s[0].data());
            int int_value = atoi(s[1].data());
//            charInfo.insert(pair<int, int>(key,int_value));
            charInfo[key] = int_value;
        }
    }
    
    unsigned char temp = 0x00;
    unsigned char command[17];
    //组装蓝牙命令02号命令
    command[0] = 0xff;
    command[1] = 0x11;
    command[2]= 0x00; //验证位
    command[3]= 0x02;
    command[4]= 0x01;
    
    int count = 5;

    for(int i=1;i<7;i++){
        map<int,int>::iterator it;
        it = charInfo.find(1);

        int value = charInfo[i];
        if(value>7){
            command[count] = 0x01<<(value-8);
            command[count+1] = 0x00;
        }else{
            command[count] = 0x00;
            command[count+1] = 0x01<<(value-1);
        }

        count +=2;
    }
    
    for (int i=0; i<17; i++) {
        temp += command[i];
    }

    command[2] = (temp^0x7f)+0x01;

    PluginHelper::sendDate(command);
    
}

MusicAnalysis::~MusicAnalysis(void){
    chordInfo.clear();
}



