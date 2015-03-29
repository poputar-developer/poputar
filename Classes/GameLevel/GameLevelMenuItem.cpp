//
//  LevelSprite.cpp
//  Guitars
//
//  Created by allen on 15-3-23.
//
//

#include "GameLevelMenuItem.h"
#include "MusicInfo.h"
#include "GuitarRunScene.h"

float itemSide = 57.0f;

GameLevelMenuItem *GameLevelMenuItem::createGameLevelMenuItem(bool isLocked,int level, int node,const ccMenuCallback& callback){
    GameLevelMenuItem *item = new GameLevelMenuItem();
    item->level = level;
    item->node = node;
    
    ui::Scale9Sprite *startMeunNormal;
    ui::Scale9Sprite *startMeunSelect;
    if(isLocked){
        startMeunNormal = ui::Scale9Sprite::create("Game_MenuItem_Normal.png");
        startMeunSelect = ui::Scale9Sprite::create("Game_MenuItem_Selected.png");
    }else{
        startMeunNormal = ui::Scale9Sprite::create("Game_MenuItem_Normal.png");
        startMeunSelect = ui::Scale9Sprite::create("Game_MenuItem_Selected.png");
    }
    
    startMeunNormal->setPreferredSize(Size(itemSide,itemSide));
    startMeunSelect->setPreferredSize(Size(itemSide,itemSide));
    
    if(item && item->initWithNormalSprite(startMeunNormal, startMeunSelect, nullptr, callback)){
        
        std::stringstream ss;
        std::string text;
        ss<<node;
        ss>>text;
        auto label = Label::create(text, "Microsoft Yahei", 27);
        label->setColor(Color3B(148, 148, 148));
        label->setPosition(Vec2(itemSide/2,itemSide/2));
        item->addChild(label);
        return item;
    }
    
    item->autorelease();
    return nullptr;
    CC_SAFE_DELETE(item);
}
//void LevelMenu::toPlaySence(Ref* sender){
//        MusicInfo *musicInfo = MusicInfo::initWithJson(0);
//
//        Scene *guitarRunScene = GuitarRun::createScene(musicInfo);
//        auto transition = TransitionFadeDown::create(0.5f, guitarRunScene);
//        Director::getInstance()->replaceScene(transition);
//    
//}