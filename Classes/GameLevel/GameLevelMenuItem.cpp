//
//  LevelSprite.cpp
//  Guitars
//
//  Created by allen on 15-3-23.
//
//

#include "GameLevelMenuItem.h"
#include "MusicInfo.h"
#include "GameRunScene.h"

//按钮大小
float itemSide = 57.0f;

GameLevelMenuItem *GameLevelMenuItem::createGameLevelMenuItem(bool isLocked, int node,const ccMenuCallback& callback){
    GameLevelMenuItem *item = new GameLevelMenuItem();
 
    ui::Scale9Sprite *startMeunNormal;
    ui::Scale9Sprite *startMeunSelect;
    if(isLocked){
        startMeunNormal = ui::Scale9Sprite::create("level/Game_MenuItem_Lock.png");
        startMeunSelect = ui::Scale9Sprite::create("level/Game_MenuItem_Lock.png");
       
    }else{
        startMeunNormal = ui::Scale9Sprite::create("level/Game_MenuItem_Normal.png");
        startMeunSelect = ui::Scale9Sprite::create("level/Game_MenuItem_Selected.png");
    }
    
    //按钮大小设置
    startMeunNormal->setPreferredSize(Size(itemSide,itemSide));
    startMeunSelect->setPreferredSize(Size(itemSide,itemSide));
    
    if(item && item->initWithNormalSprite(startMeunNormal, startMeunSelect, nullptr, callback)){
        
        
        if(isLocked){
             item->setEnabled(false);
        }else{
            item->setEnabled(true);

            std::stringstream ss;
            std::string text;
            ss<<node;
            ss>>text;
            auto label = Label::createWithTTF(text, "fonts/manhuati.ttf", 20);
            label->setColor(Color3B(148, 148, 148));
            Size itemSize = item->getContentSize();
            label->setPosition(Vec2(itemSize.width/2,itemSize.height/2-10));
            item->addChild(label);

        }
        item->autorelease();
        return item;
    }
    
    CC_SAFE_DELETE(item);
    return nullptr;
    
}