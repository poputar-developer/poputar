//
//  StartLayer.cpp
//  poputar
//
//  Created by allen on 15-4-13.
//
//

#include "StartScene.h"
#include "GuitarRunScene.h"
#include "POPTGlobal.h"

Scene* StartScene::createScene(){
    
    auto scene = Scene::create();
    auto layer = StartScene::createStartScene();
    scene->addChild(layer);
    return scene;
}

StartScene* StartScene::createStartScene(){
    StartScene *item = new StartScene();
    if(item && item->init()){//(Color4B(0, 0, 0, 120))){
        item->autorelease();
        item->setPosition(0,0);
        item->loadFrame();
        return item;
    }
    CC_SAFE_DELETE(item);
    return nullptr;
}


void StartScene::loadFrame(){
    
    isPlaying = false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    
    ui::Button *replayBtn = ui::Button::create("startVideoBg.png");
    replayBtn->setAnchorPoint(Vec2::ZERO);
    float videoImageY = (visibleSize.height-replayBtn->getContentSize().height)/2;
    replayBtn->setPosition(Vec2(20,videoImageY));
    replayBtn->addClickEventListener(CC_CALLBACK_1(StartScene::replayController, this));
    this->addChild(replayBtn,1);
    
    
    string title = poptGlobal->gni->getMusicInfo()->getTitle()+"视频演示";
    auto label = Label::createWithTTF(title, "fonts/yuanti.ttf", 30);
    label->setColor(Color3B(155, 87, 223));
    label->setAnchorPoint(Vec2::ZERO);
    label->setPosition(20,visibleSize.height - videoImageY);
    this->addChild(label);
    
    
    float y = visibleSize.height/2 - replayBtn->getContentSize().height/2;
    float x = visibleSize.width/2 + replayBtn->getContentSize().width/2 - 60;
    //跳过按钮
    skipBtn = ui::Button::create("startSkipBtn.png");
    skipBtn->setAnchorPoint(Vec2::ZERO);
    skipBtn->setPosition(Vec2(x+10,y));
    skipBtn->addClickEventListener(CC_CALLBACK_1(StartScene::skipController, this));
    this->addChild(skipBtn,1);
    
//    //自测
//    y+=skipBtn->getContentSize().height + 10;
//    ui::Button *studyBtn = ui::Button::create("startStudyBtn.png");
//    studyBtn->setAnchorPoint(Vec2::ZERO);
//    studyBtn->setPosition(Vec2(x+10,y));
//    studyBtn->addClickEventListener(CC_CALLBACK_1(StartScene::studyController, this));
//    this->addChild(studyBtn,1);
//    
    
    string Tip = "小提示：弹奏过程中注意手指按弦姿势摆放正确，按弦的时候尽量靠近品丝就能省力很多（当然不要按在品丝上），不然碰到其他的弦会不出声音哦！";
    
    auto labelTip = Label::createWithTTF(Tip, "fonts/yuanti.ttf", 12);
    labelTip->setColor(Color3B(155, 87, 223));
    labelTip->setAnchorPoint(Vec2::ZERO);
    labelTip->setPosition(20,0);
    labelTip->setDimensions(400, 40);
    this->addChild(labelTip);
}


void StartScene::showVideo(){
    Size size = Director::getInstance()->getVisibleSize();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    auto videoPlayer = POPTVideoPlayer::create();
    videoPlayer->setPosition(Point(size.width / 2, size.height / 2));
    videoPlayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    videoPlayer->setContentSize(Size(size.width , size.height));
    this->addChild(videoPlayer,1);
    if (videoPlayer){
        videoPlayer->setFullScreenEnabled(true);
        videoPlayer->setFileName("dahai.mp4");
        videoPlayer->play();
    }
    videoPlayer->addEventListener(CC_CALLBACK_2(StartScene::videoEventCallback, this));
    
    videoPlayer->setTag(1);
#endif
}

void StartScene::skipController(cocos2d::Ref *ref){
    if(!isPlaying){
        Scene *scene = GuitarRun::createScene();
        auto transition = TransitionCrossFade::create(0.5f, scene);
        Director::getInstance()->replaceScene(transition);
    }
//    if(!isPlaying){
//        Scene *scene = GuitarRun::createScene();
//        auto transition = TransitionCrossFade::create(0.5f, scene);
//        Director::getInstance()->replaceScene(transition);
//    }
}

void StartScene::replayController(cocos2d::Ref *ref){
    if(!isPlaying){
        showVideo();
        isPlaying = true;
    }
}

//void StartScene::studyController(cocos2d::Ref *ref){
//    if(!isPlaying){
//        Scene *scene = SelfTestScene::createScene();
//        auto transition = TransitionCrossFade::create(0.5f, scene);
//        Director::getInstance()->replaceScene(transition);
//    }
//}

void StartScene::videoPlayOverCallback(){
    skipBtn->loadTextureNormal("startNextBtn.png");
    removeChildByTag(1);
    isPlaying = false;
}

void StartScene::setBackground(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("startBg.png");
    sprite->setOpacity(200); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, 0);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

void StartScene::videoEventCallback(cocos2d::Ref *sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType){
    switch (eventType) {

        case cocos2d::experimental::ui::VideoPlayer::EventType::PLAYING:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::PAUSED:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::STOPPED:
            break;
        case cocos2d::experimental::ui::VideoPlayer::EventType::COMPLETED:
            videoPlayOverCallback();
            break;
        default:
            break;
    }
}
#endif

