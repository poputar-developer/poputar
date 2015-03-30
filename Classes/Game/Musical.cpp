//
//  Musical.cpp
//  poputar
//
//  Created by allen on 15-3-30.
//
//

#include "Musical.h"

Musical* Musical::createMusical(std::string filename,int key, int value,float y){

    Musical *item = new Musical();
    item->key = key;
    item->value = value;
    item->y = y;
    if(item && item->initWithFile(filename)){

        std::stringstream ss;
        std::string text;
        ss<<value;
        ss>>text;
        auto label = Label::create(text, "Microsoft Yahei", 35);
        label->setColor(Color3B(255, 90, 10));
        label->setPosition(Vec2(item->getContentSize().width/2,item->getContentSize().height/2));
        item->addChild(label);
        item->autorelease();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

ActionInterval* Musical::musicalMove(Common *common,int speed){
    float time = common->rhythm_time;
    float moveTime = time * speed;

    MoveTo *beginMove = MoveTo::create(moveTime,Vec2(common->rhythm_distance,y));
    return beginMove;
    
}

ActionInterval* Musical::musicalFadeOut(Common *common){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    int visibleWidth = visibleSize.width;
    float endSpeed= common->unitSpeed * common->leftUnit;
    MoveTo *endMove = MoveTo::create(endSpeed, Vec2(visibleWidth,y));
    FadeOut *out = FadeOut::create(endSpeed);
    Spawn *spawn = Spawn::create(endMove,out,NULL);
    return spawn;

}

