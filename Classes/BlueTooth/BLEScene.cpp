//
//  BLEScene.cpp
//  Guitars
//
//  Created by allen on 15-3-17.
//
//

#include "../Base/POPTBaseDefine.h"

using namespace cocostudio::timeline;

int connectCount=0;

ui::Text *label;

Scene* BLEScene::createScene(){

    auto scene = Scene::create();
    auto layer = BLEScene::create();
//    Node *layer = CSLoader::createNode("BLEScene.csd");
    scene->addChild(layer);
    return scene;
}

bool BLEScene::init(){
    
    if ( !Layer::init() )
    {
        return false;
    }
    auto rootNode = CSLoader::createNode("ble/BLEScene.csb");
    
    addChild(rootNode);
    
    label = (ui::Text*)rootNode->getChildByName("Text_1");
     
    schedule(schedule_selector(BLEScene::connectBle), 3.0f,kRepeatForever,0.1f);

    return true;
}
//连接蓝牙
void BLEScene::connectBle(float dt){
    connectCount++;
    log("connectCount:%i",connectCount);
    
    if(PluginHelper::isConnected()){
        label->setString("连接吉他成功");
        unschedule(schedule_selector(BLEScene::connectBle));
    }else if(connectCount >=CONNECT_CONTENT){
        label->setString("连接吉他失败");
         unschedule(schedule_selector(BLEScene::connectBle));
    }
    
    if(!PluginHelper::isConnected() && connectCount<CONNECT_CONTENT){
        PluginHelper::scanBLEPeripherals();
    }else{
        scheduleOnce(schedule_selector(BLEScene::nextSence), 2.0f);
    }
}

//跳转到下一界面
void BLEScene::nextSence(float dt){
    auto nextScene = GameLevel::createScene();
    auto transition = TransitionCrossFade::create(0.5f, nextScene);
    Director::getInstance()->replaceScene(transition);
}




