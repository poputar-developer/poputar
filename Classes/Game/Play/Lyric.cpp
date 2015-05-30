//
//  Lyric.cpp
//  poputar
//
//  Created by allen on 15-5-29.
//
//

#include "Lyric.h"
#include "POPTBaseDefine.h"

Lyric* Lyric::createLyric(float size,lyricRunModel* lrm){
    Lyric *lyric = new Lyric();
    if(lyric && lyric->init()){
        lyric->size = size;
        lyric->lrm = lrm;
        lyric->loadFrame();
        lyric->autorelease();
        return lyric;
    }
    return nullptr;
    CC_SAFE_DELETE(lyric);
}

void Lyric::loadFrame(){
    vector<LyricTonicModel*> contentVec = lrm->contentVec;
    //将单个字符组装成歌词
    for (int l=0; l<contentVec.size(); l++) {
        float x = l*size;
        LyricTonicModel* ltm = contentVec[l];
        auto lt = LyricText::createLyricText(size, ltm);
        lt->setAnchorPoint(Vec2::ZERO);
        lt->setPosition(Vec2(x,0));
        this->addChild(lt);
        
        string key = POPTStringUtils::intToString(ltm->p_index)
                     +"@|@"+
                     POPTStringUtils::intToString(ltm->s_index)
                     +"@|@"+
                     POPTStringUtils::intToString(ltm->t_index);
        
        textMap[key] = lt;
    }
}

void Lyric::changeLyricText(lyricRunModel *lrm){
    this->lrm = lrm;
    this->removeAllChildren();
    textMap.clear();
    loadFrame();
}

void Lyric::lyricChangeColor(string key){
    if(!textMap.empty() && textMap.find(key) != textMap.end()){
        LyricText* lt = textMap.at(key);
        lt->runLyricAction();
    }
}

//=======================================================================

LyricText* LyricText::createLyricText(float size,LyricTonicModel * ltm){
    LyricText *lyricText = new LyricText();
    if(lyricText && lyricText->init()){
        lyricText->ltm = ltm;
        lyricText->size = size;
        lyricText->loadFrame();
        lyricText->autorelease();
        return lyricText;
    }
    return nullptr;
    CC_SAFE_DELETE(lyricText);
}

void LyricText::loadFrame(){
    
    auto textLabel = Label::createWithSystemFont(ltm->content, "Arial",size);
    textLabel->setAnchorPoint(Vec2::ZERO);
    textLabel->setPosition(Vec2(0,-1*size/10));
    
    auto clip = ClippingNode::create(textLabel);
    auto bg = ui::Scale9Sprite::create("heise.png");
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPreferredSize(Size(size*2,size));
    clip->addChild(bg);
    clip->setInverted(true);
    clip->setAlphaThreshold(0);
//    clip->setPosition(200, 200);
    this->addChild(clip,3);
    
    auto moveSprite = ui::Scale9Sprite::create("baise.png");
    moveSprite->setAnchorPoint(Vec2::ZERO);
    moveSprite->setPreferredSize(Size(size,size));
//    moveSprite->setPosition(200, 200);
    this->addChild(moveSprite,2);

    moveNode = moveSprite;
    
    auto last = ui::Scale9Sprite::create("huangse.png");
    last->setAnchorPoint(Vec2::ZERO);
    last->setPreferredSize(Size(size,size));
//    last->setPosition(200, 200);
    this->addChild(last,1);

    log("text width:%f",        textLabel->getContentSize().width);
}


void LyricText::runLyricAction(){
    PlayConfig* config =  poptGlobal->gni->getConfig();
    float moveTime =ltm->lenght*config->unitTime;
    auto centerMove =MoveBy::create(moveTime, Vec2(size,0));
    moveNode->runAction(centerMove);
}