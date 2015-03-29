//
//  BLEScene.cpp
//  Guitars
//
//  Created by allen on 15-3-17.
//
//

#include "BLEScene.h"
#include "PluginHelper.h"
#include "SelectMusic.h"


int connectCount=0;

Label *label;

Scene* BLEScene::createScene(){

    auto scene = Scene::create();
    auto layer = BLEScene::create();
//    Node *layer = CSLoader::createNode("MainScene.csb");
    scene->addChild(layer);
    return scene;
}

bool BLEScene::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto sprite = Sprite::create("background.png");
    
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
    
    
    
    schedule(schedule_selector(BLEScene::connectBle), 3.0f,kRepeatForever,0.1f);
    
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("BlePlist.plist");
    auto animation = Animation::create();
    for (int i=1; i<3; i++) {
        std::string szName = StringUtils::format("ble/ble_loading_%d.png",i);
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(szName));
    }
    animation->setDelayPerUnit(3.0f/15.0f);
    animation->setRestoreOriginalFrame(true);
    AnimationCache::getInstance()->addAnimation(animation, "loading");
    
    auto loading = AnimationCache::getInstance()->getAnimation("loading");
    auto animate = Animate::create(loading);
    
    auto repeatanimate = RepeatForever::create(animate);
    auto animateSprite = Sprite::createWithSpriteFrameName("ble/ble_loading_1.png");
    animateSprite->runAction(repeatanimate);
    animateSprite->setPosition(Vec2(visibleSize.width/2,170));
    this->addChild(animateSprite);

    
    string text = "正在连接吉他";
    label = Label::create(text, "Marker Felt",20);
    label->setPosition(Vec2(visibleSize.width/2 ,70));
    this->addChild(label, 1);
    
    return true;
}
//连接蓝牙
void BLEScene::connectBle(float dt){
    connectCount++;
    log("connectCount:%i",connectCount);
    
    if(PluginHelper::isConnected()){
        label->setString("蓝牙连接成功");
        unschedule(schedule_selector(BLEScene::connectBle));
    }else if(connectCount >=5){
        label->setString("蓝牙连接失败");
         unschedule(schedule_selector(BLEScene::connectBle));
    }
    
    if(!PluginHelper::isConnected() && connectCount<5){
        PluginHelper::scanBLEPeripherals();
    }else{
        scheduleOnce(schedule_selector(BLEScene::nextSence), 1.0f);
    }
}
//跳转到下一界面
void BLEScene::nextSence(float dt){
    Scene *selectScene = SelectMusic::createScene();
    auto transition = TransitionCrossFade::create(0.5f, selectScene);
    Director::getInstance()->replaceScene(transition);
}




