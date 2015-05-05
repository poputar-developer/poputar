//
//  PlayChord.cpp
//  poputar
//
//  Created by allen on 15-4-29.
//
//

#include "PlayChord.h"
#include "POPTStringUtils.h"
#include "POPTGlobal.h"


PlayChord* PlayChord::createPlayChord(BeatInfo *beatInfo,string fileName, float x){
    PlayChord *chord = new PlayChord();
    if(chord && chord->initWithFile(fileName)){
        
        chord->config = (PlayConfig*)poptGlobal->gni->getConfig();
        chord->x = x;
        chord->beatInfo = beatInfo;
        
        chord->loadFrame();
        
        chord->autorelease();

        return chord;
    }
    return nullptr;
    CC_SAFE_DELETE(chord);

}


float PlayChord::strToY(int str){
    int yFlag =0;
    switch (str) {
        case 1:
            yFlag = 6;
            break;
        case 2:
            yFlag = 5;
            break;
        case 3:
            yFlag = 5;
            break;
        case 4:
            yFlag = 4;
            break;
        case 5:
            yFlag = 2;
            break;
        case 6:
            yFlag = 1;
            break;
        default:
            break;
    }
    
    return config->unitHeight*(float)yFlag;
}

void PlayChord::createBangingOut(string chordType, int startStr,int endStr){
        
        float startY = strToY(startStr);
        float endY = strToY(endStr);
        float y = startY>endY ? endY : startY;
        float rangeY = abs(startY-endY);
        this->setAnchorPoint(Vec2(0.5, 0));
//        this->setPosition(Vec2(x,y-config->stringHeight/2));
//        this->setPreferredSize(Size(10,rangeY+config->stringHeight));
    
        this->setPosition(Vec2(x,y));
        this->setPreferredSize(Size(10,rangeY));

    
    //log("PlayChord -----------stringH:%f x:%f y:%f height:%f",config->stringHeight,x,y-config->stringHeight/2,rangeY+config->stringHeight);
}


void PlayChord::loadFrame(){
    string chordType = beatInfo->chordType;
    string play = beatInfo->play;
    string stringInfo = beatInfo->stringInfo;
    
    vector<string> playInfos = POPTStringUtils::split(play, "@|@");
    
    if(!play.empty() &&play != ""){
        int startStr;
        int endStr;
        float playInfoFlag=0;
        for (int p =0; p<playInfos.size(); p++) {
            int playInfo = POPTStringUtils::stringToInt(playInfos[p]);
            if(playInfoFlag !=0){
                //如果一次弹多根，但其中又不连续的拨弦
                if((playInfoFlag +1) != playInfo ){
                    //创建之前的拨弦
                    createBangingOut(chordType, startStr,endStr);
                    //更新新的拨弦
                    startStr = playInfo;
                }
            }else{
                startStr = playInfo;
            }
            playInfoFlag = playInfo;
            endStr = playInfo;
        }
        
        //创建拨弦块
        createBangingOut(chordType,startStr,endStr);
    }

}

    