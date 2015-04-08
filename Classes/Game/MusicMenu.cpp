//
//  MusicController.cpp
//  poputar
//
//  Created by allen on 15-4-7.
//
//

#include "MusicMenu.h"

MusicMenu* MusicMenu::createMusicMenu(){
    MusicMenu *item = new MusicMenu();
    if(item && item->initWithFile("menuLayerBg.png")){
        item->autorelease();
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}

void MusicMenu::loadFrame(){
//    auto callback = [](Touch* touch,Event *event){
//        return true;
//    };
//    
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = callback;
//    listener->setSwallowTouches(true);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}
