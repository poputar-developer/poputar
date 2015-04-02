//
//  Musical.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "Musical.h"


Musical* Musical::createMusical(int key, int value,float y){

    Musical *item = new Musical();
    item->key = key;
    item->value = value;
    item->y = y;
    if(item && item->initWithFile("finger_popo.png")){
        
        item->loadFrame();
        
                item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

void Musical::loadFrame(){
    std::stringstream ss;
    std::string text;
    ss<<value;
    ss>>text;
    label = Label::create(text, "Microsoft Yahei", 35);
    label->setColor(Color3B(255, 90, 10));
    label->setPosition(Vec2(this->getContentSize().width/2,this->getContentSize().height/2));
    this->addChild(label);
    std::string key_str;
    std::stringstream keyss;
    keyss<<key;
    keyss>>key_str;
    fileName = key_str+"_"+text+".mp3";
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(fileName.data());
}
ActionInterval* Musical::musicalMove(FingerConfig *common){
    float time = common->rhythm_time;
    //从开始位置移动到节奏线位置所需时间
    float moveTime = time * common->speedBase;
    
    MoveTo *beginMove = MoveTo::create(moveTime,Vec2(common->contentWidth-common->rhythm_distance,y));
    return beginMove;
    
}

ActionInterval* Musical::musicalFadeOut(FingerConfig *common,bool isLabel){
    float endSpeed= common->unitSpeed * common->leftUnit;
    Spawn *spawn;
    if(!isLabel){
        MoveTo *endMove = MoveTo::create(endSpeed, Vec2(0,y));
        FadeOut *out = FadeOut::create(endSpeed);
        spawn = Spawn::create(endMove,out, NULL);
    }else{
        FadeOut *out = FadeOut::create(endSpeed);
        spawn = Spawn::create(out,NULL);
    }
    return spawn;
}

void Musical::runLeftAction(FingerConfig *config){
    this->runAction(musicalFadeOut(config,false));
    label->runAction(musicalFadeOut(config,true));
}

void Musical::musicalVoice(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fileName.data());
}


