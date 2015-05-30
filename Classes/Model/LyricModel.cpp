//
//  LyricModel.cpp
//  poputar
//
//  Created by allen on 15-5-24.
//
//

#include "POPTBaseDefine.h"


LyricModel* LyricModel::initWithFile(string fileName){
    LyricModel *lyric = new LyricModel();
    
    
    //读取和弦对应关系文件
    rapidjson::Document doc;
    
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile(fileName+".json");

    doc.Parse<0>(jsonInfo.c_str());
    
    if (doc.IsObject()) {
        
        int lr_index_flag=1;
        map<int,lyricRunModel*> lyricRunMap;
        
        const rapidjson::Value &mLyricRun = doc["lyricRun"];
        for (int c=0; c<mLyricRun.Size(); c++) {
            const rapidjson::Value &lyricRun = mLyricRun[c];
            const rapidjson::Value &lrContent = lyricRun["lr_content"];
            
            vector<string> contentVec = POPTStringUtils::split(lrContent.GetString(), "@|@");
            string start = contentVec[0];
            string end = contentVec[1];
            
            lyricRunModel * lrm = new lyricRunModel();
            
            bool flag = false;
            string content;
            for (int i=0; i<start.length(); i++) {
                if(start[i] =='['){
                    flag = true;
                    continue;
                }
                
                if(start[i] == ']'){
                    flag = false;
                    vector<string> contentVec = POPTStringUtils::split(content, ":");
                    string lr_flag = contentVec[0];
                    int lr_index = POPTStringUtils::stringToInt(contentVec[1]);
                    if(lr_flag == "p"){
                        lrm->s_pIndex = lr_index;
                    }else if(lr_flag == "s"){
                        lrm->s_sIndex = lr_index;
                    }else if(lr_flag == "t"){
                        lrm->s_tIndex = lr_index;
                    }
                    content="";
                    continue;
                }
                if (flag) {
                    content+=start[i];
                }
            }
            
            for (int i=0; i<end.length(); i++) {
                if(end[i] =='['){
                    flag = true;
                    continue;
                }
                if(end[i] == ']'){
                    flag = false;
                    vector<string> contentVec = POPTStringUtils::split(content, ":");
                    string lr_flag = contentVec[0];
                    int lr_index = POPTStringUtils::stringToInt(contentVec[1]);
                    if(lr_flag == "p"){
                        lrm->e_pIndex = lr_index;
                    }else if(lr_flag == "s"){
                        lrm->e_sIndex = lr_index;
                    }else if(lr_flag == "t"){
                        lrm->e_tIndex = lr_index;
                    }
                    content="";
                    continue;
                }
                if (flag) {
                    content+=end[i];
                }
            }
            
            lyricRunMap[lr_index_flag] = lrm;
            lr_index_flag+=1;
        }
        
        
        lr_index_flag=1;
        //一句歌词内容
//        string lr_content_flag;
        
        const rapidjson::Value &mLyrics = doc["lyrics"];
        
        for (rapidjson::SizeType l=0; l<mLyrics.Size(); l++) {
            LyricPlayModel *pModel = new LyricPlayModel();
            
            const rapidjson::Value &lyrics = mLyrics[l];
            const rapidjson::Value &pIndex = lyrics["p_index"];
            const rapidjson::Value &lyricInfo = lyrics["lyricInfo"];
            
            for (rapidjson::SizeType p=0; p<lyricInfo.Size(); p++) {
                const rapidjson::Value &sLyricInfo = lyricInfo[p];
                const rapidjson::Value &sIndex = sLyricInfo["s_index"];
                const rapidjson::Value &sLyrics = sLyricInfo["lyrics"];
                
                LyricSectionModel* sModel = new LyricSectionModel();
                for (rapidjson::SizeType s=0; s<sLyrics.Size(); s++) {
                    
                    LyricTonicModel* tModel = new LyricTonicModel();
                    const rapidjson::Value &tLyricInfo = sLyrics[s];
                    const rapidjson::Value &tIndex = tLyricInfo["t_index"];
                    const rapidjson::Value &tLyric = tLyricInfo["lyric"];
                    const rapidjson::Value &tLenght = tLyricInfo["lenght"];
                    tModel->p_index = pIndex.GetInt();
                    tModel->s_index = sIndex.GetInt();
                    tModel->t_index = tIndex.GetInt();
                    tModel->content = tLyric.GetString();
                    tModel->lenght = tLenght.GetDouble();
                    
                    sModel->lyricTonicMap[tIndex.GetInt()] = tModel;
                    int p_index = tModel->t_index;
                    int s_index = tModel->s_index;
                    int t_index = tModel->t_index;
                    
                    lyricRunModel* lrm =  lyricRunMap.at(lr_index_flag);
                    int startPIndex = lrm->s_pIndex;
                    int startSIndex = lrm->s_sIndex;
//                    int startTIndex = lrm->s_tIndex;
                    int endPIndex = lrm->e_pIndex;
                    int endSIndex = lrm->e_sIndex;
                    int endTIndex = lrm->e_tIndex;
                    
                    bool endFlag = false;
                    
                    if(startPIndex == endPIndex){
                        if(startSIndex == endSIndex){
                            if(endTIndex == t_index){
                                endFlag = true;
                            }
                        }else if(s_index == endSIndex){
                            if(t_index == endTIndex){
                                endFlag = true;
                            }
                        }
                    }else if(p_index == endTIndex){
                        if(s_index == endSIndex){
                            if(t_index == endTIndex){
                                endFlag = true;
                            }
                        }
                    }
                    
                    lrm->contentVec.push_back(tModel);
                    
                    if(endFlag){
                        lyric->lyricContentMap[lr_index_flag] = lrm;
                        lr_index_flag+=1;
                    }
                    
                }
                
                pModel->lyricSectionMap[sIndex.GetInt()] = sModel;
            }
            
            lyric->lyricPlayMap[pIndex.GetInt()] = pModel;
        }
       
    }
    
    return lyric;
}


//map<int,LyricPlayModel*> LyricModel::getPlayMap(){
//    return lyricPlayMap;
//}


map<int,lyricRunModel*> LyricModel::getContentMap(){
    return lyricContentMap;
}

//LyricTonicModel* LyricModel::getTonicModel(int p, int s, int t){
//    LyricPlayModel* playModel =  this->lyricPlayMap.at(p);
//    LyricSectionModel*sectionModel =  playModel->lyricSectionMap.at(s);
//    LyricTonicModel* tonicModel =  sectionModel->lyricTonicMap.at(t);
//    return tonicModel;
//}

void LyricModel::unLoadLyric(){
    lyricPlayMap.clear();
    lyricContentMap.clear();
}