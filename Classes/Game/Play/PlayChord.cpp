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


PlayChord* PlayChord::createPlayChord(BeatInfo *beatInfo,string lineFileName,string circleFileName, float x){
    PlayChord *chord = new PlayChord();
    if(chord && chord->initWithFile(lineFileName)){
        
        chord->config = (PlayConfig*)poptGlobal->gni->getConfig();
        chord->x = x;
        chord->beatInfo = beatInfo;
        
        chord->loadFrame(circleFileName);
        
        chord->autorelease();

        return chord;
    }
    return nullptr;
    CC_SAFE_DELETE(chord);

}



void PlayChord::createBangingOut(string chordType, int startStr,int endStr,int upOrDownFlag){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    float startY = strToY(startStr);
    float endY = strToY(endStr);
    float y = startY>endY ? endY : startY;
    float rangeY = abs(startY-endY);
    this->setAnchorPoint(Vec2(0.5, 0));
    
    //-------闪烁条多出的部分--------
    float addSide = visibleSize.height/30;
    //向上时
    if(upOrDownFlag==1){
        y -=addSide;
    }
    rangeY+=addSide;
    //-----------------------------
    
    
    this->setPosition(Vec2(x,y));
    this->setPreferredSize(Size(getContentSize().width,rangeY));
    
   
}


void PlayChord::loadFrame(string circleFileName){
    string chordType = beatInfo->chordType;
    string play = beatInfo->play;
    string stringInfo = beatInfo->stringInfo;
    //新建扫弦
    vector<string> playInfos = POPTStringUtils::split(play, "@|@");
    if(!play.empty() &&play != ""){
        int startStr;
        int endStr;
        float playInfoFlag=0;
        int upOrDownFlag = 0; //1 代表向上 2代表向下
        for (int p =0; p<playInfos.size(); p++) {
             int playInfo = POPTStringUtils::stringToInt(playInfos[p]);
            if(playInfoFlag == 0){
                startStr = playInfo;
            }else if(upOrDownFlag == 0){
                upOrDownFlag =  playInfo - playInfoFlag >0 ? 1 : 2;
            }
            playInfoFlag = playInfo;
            endStr = playInfo;
        }
        
        //创建拨弦块
        createBangingOut(chordType,startStr,endStr,upOrDownFlag);
        
        auto circle = Sprite::create(circleFileName);
        float x = this->getContentSize().width/2;
        float y;
        if(upOrDownFlag == 1){
            y = this->getContentSize().height;
        }else if(upOrDownFlag == 2){
            y=0;
        }
        circle->setPosition(Vec2(x,y));
        this->addChild(circle);
    }

}

    