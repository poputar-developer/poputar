//
//  Lyric.cpp
//  Guitars
//
//  Created by allen on 14-12-4.
//
//

#include "Lyric.h"

bool Lyric::init(){
    Sprite::init();
    return true;
}

void Lyric::setLyircStr(string lyirc){
    removeAllChildren();
    auto lyircLable = Label::createWithTTF(lyirc, "fonts/manhuati.ttf", 15);
    float height = lyircLable->getContentSize().height;
    float width = lyircLable->getContentSize().width;
    Size contentSize = Size(width, height);
    //暂时使用lable的大小
    lyircLable->setPosition(Vec2(width/2,0));
    lyircLable->setColor(Color3B(255,255,255));
    setContentSize(contentSize);
    addChild(lyircLable);
}

