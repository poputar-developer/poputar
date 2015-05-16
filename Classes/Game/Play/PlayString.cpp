//
//  PlayString.cpp
//  poputar
//
//  Created by allen on 15-5-14.
//
//

#include "PlayString.h"
#include "POPTGlobal.h"
#include "POPTBaseDefine.h"

PlayString* PlayString::createPlayString(string strInfo,string cop,string circleFileName,float x){
    PlayString *chord = new PlayString();
    if(chord && chord->initWithFile(circleFileName)){
        chord->config = (PlayConfig*)poptGlobal->gni->getConfig();
        chord->x = x;
        chord->loadFrame(strInfo,cop,circleFileName);
        chord->autorelease();
        return chord;
    }
    return nullptr;
    CC_SAFE_DELETE(chord);
}

void PlayString::loadFrame(string strInfo,string cop,string circleFileName){
    
    auto *l = Label::createWithTTF(cop, "fonts/yuanti.ttf", 30);
    l->setColor(Color3B::BLACK);
    l->setPosition(this->getContentSize().width/2,this->getContentSize().height/2);
    this->addChild(l);
    
    int str4Int = POPTStringUtils::stringToInt(strInfo);
    float y = strToY(str4Int);
    this->setPosition(Vec2(x,y));
}