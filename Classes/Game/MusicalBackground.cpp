//
//  MusicalBackground.cpp
//  poputar
//
//  Created by allen on 15-3-31.
//
//

#include "MusicalBackground.h"
#include "POPTStringUtils.h"
#include "Musical.h"

MusicalBackground* MusicalBackground::createMusicalBackground(FingerConfig *config,float oneY,float sixY){
    MusicalBackground *item = new MusicalBackground();
    if(item && item->initWithFile("background.png")){
        loadFrame(item,config,oneY,sixY);
        item->setAnchorPoint(Vec2::ZERO);
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;

}

void MusicalBackground::loadFrame(MusicalBackground *item,FingerConfig *config,float oneY,float sixY){
    //按份数分的没歌单元格的距离
    int allUnit = config->beat+config->leftUnit;
    float unitWidth = config->contentWidth/allUnit;
    //创建竖线
    for (int i = 0 ; i<allUnit; i++) {
        ui::Scale9Sprite *line = ui::Scale9Sprite::create("finger_rhythm.png");
        line->setPreferredSize(Size(line->getContentSize().width, sixY-oneY));
        line->setAnchorPoint(Vec2(0.5,0));
//        log("%f",line->getContentSize().width);
        line->setPosition(Vec2(unitWidth*i,oneY));
        item->addChild(line);
    }
}

float MusicalBackground::getSecMove(FingerConfig *config){
    float time = config->rhythm_time;
    //从开始位置移动到节奏线位置所需时间
    float moveTime = time * config->speedBase;
    //开始位置到节奏线位置的距离
    float moveDistance = config->rhythm_distance;
    //每秒移动距离
    float secMove = moveDistance/moveTime;
    log("没秒移动距离：%f",secMove);

    return secMove;
}


//int currentMusical = 0;

void MusicalBackground::createMusical(MusicInfo *musicInfo,ValueMapIntKey stringMap){
//    ValueVector musicals = musicInfo->getMusical();
//    if(currentMusical<musicals.size()){
//        Value musical = musicals.at(currentMusical-1);
//        
//        vector<string> infos = POPTStringUtils::split(musical.asString(), "@|@");
//        map<int,int> charInfo;
//        
//        for(size_t i=0;i<infos.size();i++){
//            string info = infos[i];
//            if(info.length()>0){
//                vector<string> s = POPTStringUtils::split(info, ":");
//                int key = atoi(s[0].data()); //弦位置
//                int value = atoi(s[1].data()); //品位置
//                
//                float y = stringMap[key].asFloat();
//                auto musicalSprite = Musical::createMusical(key,value,y);
//                musicalSprite->setScale(0.5);
//                
//                this->addChild(musicalSprite,2);
//            }
//        }
//        
//    }
//    currentMusical +=1;
}


ActionInterval* MusicalBackground::MucsicalBackgroundMove(FingerConfig *config){
    float time = config->rhythm_time;
    int allUnit = config->beat+config->leftUnit;
    float allTime = time *allUnit;
    MoveBy *beginMove = MoveBy::create(allTime*2,Vec2(-config->contentWidth*2,0));
    return beginMove;

}
