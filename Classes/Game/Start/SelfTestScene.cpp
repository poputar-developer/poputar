//
//  SelfTestScene.cpp
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#include "SelfTestScene.h"
#include "StartScene.h"
#include "GuitarRunScene.h"
#include "FingerRunLayer.h"
#include "POPTGlobal.h"


Scene* SelfTestScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = SelfTestScene::create();
    
    float visbleHeight=1.0f;

    //初始化游戏界面
    string type = poptGlobal->gni->getType();
//    string testMusicInfo = poptGlobal->gni->getMusic()+"_test";
    auto musicInfo = MusicInfo::initWithJson(poptGlobal->gni->getMusic());
    //C代表和弦界面 F代表指弹界面
    float gameProprotion = 0.8f;
    auto runLayer = FingerRunLayer::createFingerRunLayer(musicInfo,gameProprotion);
    layer->addChild(runLayer,1);
    runLayer->endAnimationSetting();
    
    //剩下的比例
    float resultPorprotion = visbleHeight-gameProprotion;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float sideHeight = visibleSize.height*resultPorprotion/2;
    
    //节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("snare.caf");
    layer->setBackground();
    layer->loadTopFrame(sideHeight);
    layer->loadFootFrame(sideHeight);
    scene->addChild(layer);
    return scene;
}

//加载头部组件
void SelfTestScene::loadTopFrame(float height){
//    //设置黑色背景
//    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("sideBg.png");
//    bg->setPreferredSize(Size(visibleSize.width,height));
//    bg->setAnchorPoint(Vec2::ZERO);
//    bg->setPosition(0,visibleSize.height-height);
//    this->addChild(bg,2);
//    
    
    //帮助
    ui::Button *gobackBtn = ui::Button::create("testHelperBtn.png");
    gobackBtn->setScale(0.6);
    gobackBtn->setPosition(Vec2(visibleSize.width-gobackBtn->getContentSize().width/2,visibleSize.height-height/2-5));
    gobackBtn->addClickEventListener(CC_CALLBACK_1(SelfTestScene::goBack, this));
    this->addChild(gobackBtn);
    
}

//加载底部组件
void SelfTestScene::loadFootFrame(float height){
    
//    //设置背景
    ui::Scale9Sprite* bg = ui::Scale9Sprite::create("testFootBg.png");
    bg->setPreferredSize(Size(visibleSize.width,bg->getContentSize().height));
    bg->setAnchorPoint(Vec2::ZERO);
    bg->setPosition(Vec2::ZERO);
    this->addChild(bg,2);
    
    string Tip = "小提示：弹奏过程中注意手指按弦姿势摆放正确，按弦的时候尽量靠近品丝就能省力很多（当然不要按在品丝上），不然碰到其他的弦会不出声音哦！";
    
    auto labelTip = Label::createWithTTF(Tip, "fonts/yuanti.ttf", 12);
    labelTip->setColor(Color3B(155, 87, 223));
    labelTip->setAnchorPoint(Vec2::ZERO);
    labelTip->setPosition(50,0);
    labelTip->setDimensions(300, bg->getContentSize().height-5);
    bg->addChild(labelTip);

    
    
    //返回
    ui::Button *gobackBtn = ui::Button::create("testSkipBtn.png");
    gobackBtn->setScale(0.6);
    gobackBtn->setPosition(Vec2(visibleSize.width-gobackBtn->getContentSize().width/2,bg->getContentSize().height/2));
    gobackBtn->addClickEventListener(CC_CALLBACK_1(SelfTestScene::goBack, this));
    bg->addChild(gobackBtn);
    
}

//设置背景
void SelfTestScene::setBackground(){
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("background.png");
    sprite->setOpacity(200);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}


void SelfTestScene::goBack(cocos2d::Ref *sender){
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("snare.caf");
    auto startScene = StartScene::createScene();
    Director::getInstance()->replaceScene(startScene);
}


void SelfTestScene::goOnController(cocos2d::Ref *ref){
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("snare.caf");
    auto runScene = GuitarRun::createScene();
    Director::getInstance()->replaceScene(runScene);
    
}
