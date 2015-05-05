//
//  MusicInfo.cpp
//  Guitar
//  
//  Created by allen on 14-11-30.
//
//

#include "MusicInfo.h"
#include "cocostudio/CocoStudio.h"



MusicInfo* MusicInfo::initWithJson(string uuid){
    MusicInfo *music = new MusicInfo();
    
    //读取和弦对应关系文件
    rapidjson::Document doc;

    std::string jsonInfo =FileUtils::getInstance()->getStringFromFile(uuid+".json");
    
    doc.Parse<0>(jsonInfo.c_str());
    
    if(!doc.IsObject()){
        log("music file is error!");
    }
    
    const rapidjson::Value &mType = doc["type"];
    const rapidjson::Value &mTitle = doc["title"];
    const rapidjson::Value &mBpm = doc["bpm"];
    const rapidjson::Value &mBeat = doc["beat"];
    const rapidjson::Value &mMusic = doc["music"];
    
    music->title = mTitle.GetString();
    music->musicFile= mMusic.GetString();
    music->beat=mBeat.GetInt();
    music->bpm=mBpm.GetInt();
    
    string type =mType.GetString();
    
    if( type == "C"){
        const rapidjson::Value &cArray = doc["chords"];
        if(!cArray.IsArray()){
            log("music file chords array is error!");
        }
        
        int count =0;
        ValueVector beatVector;
        ValueVector lyricVector;
        for(rapidjson::SizeType i=0;i<cArray.Size();i++){
            //按小节拍数进行组装(如每小节4拍则4个和弦装入一个vector中)
            if(count == mBeat.GetInt()){
                count = 0;
                ValueVector tempBeatVector = beatVector;
                ValueVector tempLyricVector = lyricVector;
                music->vec_chords.push_back(Value(tempBeatVector));
                music->vec_lyric.push_back(Value(tempLyricVector));
                beatVector.clear();
                lyricVector.clear();

            }
            const rapidjson::Value &str = cArray[i];
            const rapidjson::Value &cType = str["type"];
            const rapidjson::Value &cLyric_p = str["lyric_position"];
            const rapidjson::Value &cLyric_c = str["lyric_content"];
            string chordType = cType.GetString();
            string lyricContent = cLyric_c.GetString();
            beatVector.push_back(Value(chordType));
            lyricVector.push_back(Value(lyricContent));
             music->bluetoothChord.push_back(chordType);
            count++;
        }
        //如果最后有剩余和弦或歌词，则单独组装一个vector
        if(beatVector.size()>0){
            music->vec_chords.push_back(Value(beatVector));
        }
        if(lyricVector.size()>0){
            music->vec_lyric.push_back(Value(lyricVector));

        }
        
    }else if(type == "F"){
        const rapidjson::Value &cArray = doc["strings"];
        if(!cArray.IsArray()){
            log("music file chords array is error!");
        }
        
        for(rapidjson::SizeType i=0;i<cArray.Size();i++){
            const rapidjson::Value &strs = cArray[i];
            const rapidjson::Value &cString = strs["str"];
            string str = cString.GetString();
            music->vec_musical.push_back(Value(str));
        }
    }else if(type=="Finger"){
//        const rapidjson::Value &cSections = doc["sections"];
//        for (rapidjson::SizeType s=0; s<cSections.Size(); s++) {
//            const rapidjson::Value &section = cSections[s];
//            const rapidjson::Value &cChord = section["chord"];
//            const rapidjson::Value &cMusicals = section["musicals"];
//            
//            SectionInfo* sectionVO = new SectionInfo();
//            sectionVO->chordInfo = cChord.GetString();
//            for (rapidjson::SizeType m=0; m<cMusicals.Size(); m++) {
//                const rapidjson::Value &musical = cMusicals[m];
//                const rapidjson::Value &beat = musical["beat"];
//                const rapidjson::Value &string = musical["string"];
//                MusicalInfo* musicalVO = new MusicalInfo();
//                musicalVO->beat = beat.GetDouble();
//                musicalVO->stringInfo = string.GetString();
//                sectionVO->musicals.push_back(musicalVO);
//            }
//            music->sections.push_back(sectionVO);
//        }
    }

    return music;
}

int MusicInfo::getBeat(){
    return this->beat;
}

int MusicInfo::getBpm(){
    return this->bpm;
}

ValueVector MusicInfo::getMusical(){
    return this->vec_musical;
}

ValueVector MusicInfo::getChords(){
    return this->vec_chords;
}

ValueVector MusicInfo::getLyircs(){
    return this->vec_lyric;
}

string MusicInfo::getTitle(){
    return this->title;
}

string MusicInfo::getMusicFile(){
    return this->musicFile;
}

vector<string> MusicInfo::getBluetoothChord(){
    return bluetoothChord;
}
