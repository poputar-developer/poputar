//
//  Musical.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "Musical.h"
#include "POPTStringUtils.h"
Musical* Musical::createMusical(FingerConfig* fingerConfig, string content,float unitHeight){
    Musical *item = new Musical();
    if(item && item->initWithFile("game/finger/finger_rhythm.png")){
        
        float unitHeight = fingerConfig->contentHeight/7;
        float musicalHeight = unitHeight*5;
        item->y = unitHeight;
        item->setAnchorPoint(Vec2(0.5,0));
        item->setPosition(Vec2(fingerConfig->contentWidth,unitHeight));
        item->setPreferredSize(Size(item->getContentSize().width,musicalHeight));
        item->loadMusical(content,unitHeight);
        
        item->autorelease();
       
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

Musical* Musical::createMusical(FingerConfig* fingerConfig, string content,float unitHeight,float x){
    Musical *item = new Musical();
    if(item && item->initWithFile("game/finger/finger_rhythm.png")){
        
        float unitHeight = fingerConfig->contentHeight/7;
        float musicalHeight = unitHeight*5;
        item->y = unitHeight;
        item->setAnchorPoint(Vec2(0.5,0));
        item->setPosition(Vec2(x,unitHeight));
        item->setPreferredSize(Size(item->getContentSize().width,musicalHeight));
        item->loadMusical(content,unitHeight);
        
        item->autorelease();
        
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}



void Musical::loadMusical(string content,float unitHeight){
    this->content = content;
    
    vector<string> infos = POPTStringUtils::split(content, "@|@");
    map<int,int> charInfo;
    
    for(size_t i=0;i<infos.size();i++){
        string info = infos[i];
        if(info.length()>0){
            vector<string> s = POPTStringUtils::split(info, ":");
            //弦位置
            int key = atoi(s[0].data());
            //品位置
            int value = atoi(s[1].data());
            int strTemp;
            
            switch (key) {
                case 1:
                    strTemp = 5;
                    break;
                case 2:
                    strTemp = 4;
                    break;
                case 3:
                    strTemp = 3;
                    break;
                case 4:
                    strTemp = 2;
                    break;
                case 5:
                    strTemp = 1;
                    break;
                case 6:
                    strTemp = 0;
                    break;
                    
                default:
                    break;
            }
            
        
            float y = strTemp*unitHeight;
            
            auto musical = ui::Scale9Sprite::create("game/finger/finger_popo.png");
            musical->setScale(0.5);
            musical->setPosition(this->getContentSize().width/2,y);
            
            std::string value_str = POPTStringUtils::intToString(value);
            auto label = Label::createWithTTF(value_str, "fonts/manhuati.ttf", 35);
            label->setColor(Color3B(255, 255, 255));
            label->setPosition(Vec2(musical->getContentSize().width/2,musical->getContentSize().height/2-15));
            musical->addChild(label);
        
            if(key != 1){
                while (1) {
                    
                    int valueFlag = 5;
                    if(key == 3){
                        valueFlag = 4;
                    }
                    
                    if(value>=valueFlag){
                        key-=1;
                        value-=valueFlag;
                    }else{
                        break;
                    }
                }
            }
            
            std::string key_voice_str= POPTStringUtils::intToString(key);
            std::string value_voice_str= POPTStringUtils::intToString(value);
            
            
            std::string fileName = key_voice_str+"_"+value_voice_str+".mp3";

            std::string path = "audio/finger/"+fileName;
            voiceFileName.push_back(Value(path));
            CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(path.data());
            
            this->addChild(musical,2);
            
            stringsInfo.push_back(Value(key));
            
            

        }
    }

}

ActionInterval* Musical::musicalMove(FingerConfig *common,float unitWidth){
    float time = common->rhythm_time;
    //从开始位置移动到节奏线位置所需时间
    float moveTime = time * common->beat;
    float distance = common->rhythm_distance;
    
    float allTime = common->contentWidth/(distance/moveTime);
    
    MoveTo *beginMove = MoveTo::create(allTime*2,Vec2(-common->contentWidth-unitWidth,y));
    return beginMove;
    
}


void Musical::musicalVoice(float capoValue){
    for (int i=0 ; i<voiceFileName.size(); i++) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(voiceFileName[i].asString().data(),false,capoValue,0,1);
    }
}

string  Musical::getContent(){
    return this->content;
}

ValueVector Musical::getStringsInfo(){
    return this->stringsInfo;
}

