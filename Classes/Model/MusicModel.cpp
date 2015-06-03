//
//  MusicModel.cpp
//  poputar
//
//  Created by allen on 15-4-27.
//
//

#include "../Base/POPTBaseDefine.h"

MusicModel* MusicModel::initWithFile(string fileName){
    MusicModel *music = new MusicModel();

    //读取和弦对应关系文件
    rapidjson::Document doc;
    
    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile(fileName+".json");
    
    doc.Parse<0>(jsonInfo.c_str());
    
    if(!doc.IsObject()){
        log("music file is error!");
    }
    
    const rapidjson::Value &mType = doc["type"];
    const rapidjson::Value &mKey = doc["key"];
    const rapidjson::Value &mTitle = doc["title"];
    const rapidjson::Value &mBpm = doc["bpm"];
    const rapidjson::Value &mBeatFlag = doc["beatFlag"];
    const rapidjson::Value &mPlays = doc["plays"];
    const rapidjson::Value &mSections = doc["sections"];
    
    music->type = mType.GetString();
    music->key = mKey.GetString();
    music->title = mTitle.GetString();
    vector<string> beatInfo= POPTStringUtils::split(mBeatFlag.GetString(), ":");
    music->beatRef=POPTStringUtils::stringToInt(beatInfo[0]);
    music->beatFlag=POPTStringUtils::stringToInt(beatInfo[1]);
    music->bpm=mBpm.GetInt();
    

    //读取音乐文件中的播放模式信息
    for (rapidjson::SizeType p=0; p<mPlays.Size(); p++) {
        MusicPlayInfo* playInfo = new MusicPlayInfo();
        const rapidjson::Value &play = mPlays[p];
        const rapidjson::Value &index = play["p_index"];
        const rapidjson::Value &range = play["range"];
        playInfo->p_index = index.GetInt();
        vector<string> rangeInfo= POPTStringUtils::split(range.GetString(), ":");
        playInfo->startSection=POPTStringUtils::stringToInt(rangeInfo[0]);
        playInfo->endSection=POPTStringUtils::stringToInt(rangeInfo[1]);
        
        music->plays[index.GetInt()] = playInfo;
    }
    
    //读取小节信息
    for (rapidjson::SizeType s=0; s<mSections.Size(); s++) {
        SectionInfo *sectionInfo = new SectionInfo();
        const rapidjson::Value &section = mSections[s];
        const rapidjson::Value &sIndex = section["s_index"];
        sectionInfo->s_index = sIndex.GetInt();
        //读取主音信息
        const rapidjson::Value &tonics = section["tonics"];
        
        if(!tonics.IsNull()){
            for (rapidjson::SizeType t =0; t<tonics.Size(); t++) {
                TonicInfo *toincInfo = new TonicInfo();
                const rapidjson::Value &tTonic = tonics[t];
                const rapidjson::Value &index = tTonic["t_index"];
                toincInfo->t_index = index.GetInt();
                const rapidjson::Value &note = tTonic["note"];
                const rapidjson::Value &length = tTonic["length"];
                toincInfo->note = note.GetString();
                toincInfo->length = length.GetDouble();
                sectionInfo->tonics[index.GetInt()] = toincInfo;
                
            }
        }
        
        //读取和弦信息
        const rapidjson::Value &beats = section["beats"];
        if(beats.IsObject()){
            
        
        for (rapidjson::SizeType b =0; b<beats.Size(); b++) {
            BeatInfo *beatInfo = new BeatInfo();
            const rapidjson::Value &bBeat = beats[b];
            const rapidjson::Value &index = bBeat["b_index"];
            const rapidjson::Value &chord = bBeat["chord"];
            const rapidjson::Value &length = bBeat["length"];
            const rapidjson::Value &play = bBeat["play"];
            const rapidjson::Value &stringInfo = bBeat["string"];
            beatInfo->length = length.GetDouble();
            if(!chord.IsNull()){
                beatInfo->chordType = chord.GetString();
            }
            if(!play.IsNull()){
                beatInfo->play=play.GetString();
            }
            if (!stringInfo.IsNull()) {
                beatInfo->stringInfo= stringInfo.GetString();
            }
            sectionInfo->beats[index.GetInt()] = beatInfo;
//            sectionInfo->beats.push_back(beatInfo);
        }
        }
        music->sections[sIndex.GetInt()]=sectionInfo;
    }
    
    
    LyricModel* lyricModel = LyricModel::initWithFile(fileName+"_lyric");
    music->lyricModel = lyricModel;
    
    return music;
}

string MusicModel::getType(){
    return type;
}
string MusicModel::getKey(){
    return key;
}
string MusicModel::getTitle(){
    return title;
}
int MusicModel::getBeatFlag(){
    return beatFlag;
}
int MusicModel::getBeatRef(){
    return beatRef;
}
int MusicModel::getBpm(){
    return bpm;
}
map<int,SectionInfo*> MusicModel::getSections(){
    return sections;
}
map<int,MusicPlayInfo*> MusicModel::getPlayInfo(){
    return plays;
}

LyricModel* MusicModel::getLyricModel(){
    return lyricModel;
}

void MusicModel::unLoadMusicModel(){
    plays.clear();
    sections.clear();
    
    lyricModel->unLoadLyric();
    delete lyricModel;
}