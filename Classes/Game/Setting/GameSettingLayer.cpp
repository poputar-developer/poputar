//
//  GameSettingLayer.cpp
//  poputar
//
//  Created by shigq on 15/6/1.
//
//

#include "GameSettingLayer.h"


USING_NS_CC;
using namespace ui;

Scene* GameSetting::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameSetting::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameSetting::init() {
    if (!Layer::init())
    {
        return false;
    }
    this->initWithColor(Color4B(0,0,0,200));
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //开始调弦按钮
    startTuningBtn = Button::create("game/setting/startTuningBtn.png");
    startTuningBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 168));
    startTuningBtn->setTitleText("开始调弦");
    startTuningBtn->setTitleFontSize(30);
    startTuningBtn->setTitleColor(Color3B(230, 230, 230));
    this->addChild(startTuningBtn, 2);
    
    //蓝牙设备按钮
    auto bluetoolthfile = "game/setting/bluetoothEnable.png";
    if ("N" == UserDefault::getInstance()->getStringForKey("bluetoolthOpen")) {
        bluetoolthfile = "game/setting/bluetoothDisable.png";
    }
    bluetoolthBtn = Button::create(bluetoolthfile);
    bluetoolthBtn->setPosition(Vec2(visibleSize.width / 2 - 171, visibleSize.height/2));
    bluetoolthBtn->addClickEventListener(CC_CALLBACK_1(GameSetting::bluetoolthBtnClick, this));
    this->addChild(bluetoolthBtn, 2);
    
    //蓝牙设备信息
    bluetoolthTxt = Text::create("连接设备", "微软雅黑", 30);
    bluetoolthTxt->setPosition(Vec2(visibleSize.width / 2 - 171, visibleSize.height / 2 - 80));
    this->addChild(bluetoolthTxt, 2);
    
    
    //蓝牙设备列表
    bluelistView = ListView::create();
    bluelistView->setSize(Size(248, 177));
    bluelistView->setPosition(Vec2(visibleSize.width / 2 - 230, visibleSize.height / 2 - bluetoolthBtn->getContentSize().height - bluetoolthTxt->getContentSize().height - 177));
    bluelistView->setBounceEnabled(true);
    this->addChild(bluelistView, 2);
    
    //背景音按钮
    auto bgMusicfile = "game/setting/bgMusicEnable.png";
    if ("N" == UserDefault::getInstance()->getStringForKey("isBgMusic")) {
        bgMusicfile = "game/setting/bgMusicDisable.png";
    }
    else {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("video/s3.wav", true);
    }
    bgMusicBtn = Button::create(bgMusicfile);
    bgMusicBtn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    bgMusicBtn->addClickEventListener(CC_CALLBACK_1(GameSetting::bgMusicBtnClick, this));
    this->addChild(bgMusicBtn, 2);
    
    
    //背景音信息
    auto bgMusicTxt = Text::create("背景音", "微软雅黑", 30);
    bgMusicTxt->setColor(Color3B::WHITE);
    bgMusicTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 -80));
    this->addChild(bgMusicTxt, 2);
    
    
    
    //调弦页定时开启
    auto tuningfile = "game/setting/tuningBtnEnable.png";
    if ("N" == UserDefault::getInstance()->getStringForKey("isTuning")) {
        tuningfile = "game/setting/tuningBtnDisable.png";
    }
    tuningBtn = Button::create(tuningfile);
    tuningBtn->setPosition(Vec2(visibleSize.width / 2 + 171, visibleSize.height / 2));
    tuningBtn->addClickEventListener(CC_CALLBACK_1(GameSetting::tuningBtnClick, this));
    this->addChild(tuningBtn, 2);
    
    
    //调弦页定时开启信息
    auto tuningTxt = Text::create("调弦页定时开启", "微软雅黑", 30);
    tuningTxt->setColor(Color3B::WHITE);
    tuningTxt->setPosition(Vec2(visibleSize.width / 2 + 171, visibleSize.height / 2 - 80));
    this->addChild(tuningTxt, 2);
    
    //关闭按钮
    auto closeBtn = Button::create("game/setting/close.png");
    closeBtn->setPosition(Vec2(visibleSize.width - 74, visibleSize.height - 58));
    closeBtn->addClickEventListener(CC_CALLBACK_1(GameSetting::closeBtnClick, this));
    this->addChild(closeBtn, 2);
    
    //if (UserDefault::getInstance()->getStringForKey("isBgMusic") != "N") {
    //CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("video/s3.wav", true);
    //}
    
    
    return true;
}

//===============================================按钮响应事件============================================

void GameSetting::closeBtnClick(cocos2d::Ref *ref){
    //Director::getInstance()->popScene();
    this->getParent()->removeChild(this);
}

//蓝牙设备按钮 响应事件处理方法
void GameSetting::bluetoolthBtnClick(Ref* pSender) {
    //暂时设置从文件读取，后续需读取设备蓝牙开启状态
    if ("N" == UserDefault::getInstance()->getStringForKey("bluetoolthOpen")) {
        initGitarList();
        bluetoolthBtn->loadTextureNormal("game/setting/bluetoothEnable.png");
        UserDefault::getInstance()->setStringForKey("bluetoolthOpen", "Y");
    }
    else {
        bluetoolthBtn->loadTextureNormal("game/setting/bluetoothDisable.png");
        UserDefault::getInstance()->setStringForKey("bluetoolthOpen", "N");
        if (bluelistView != NULL) {
            bluelistView->removeAllItems();
        }
        if (connBluelistView != NULL) {
            connBluelistView->setVisible(false);
        }
    }
}

//背景音按钮 响应事件处理方法
void GameSetting::bgMusicBtnClick(Ref* pSender) {
    if ("N" == UserDefault::getInstance()->getStringForKey("isBgMusic")) {
        UserDefault::getInstance()->setStringForKey("isBgMusic", "Y");
        bgMusicBtn->loadTextureNormal("game/setting/bgMusicEnable.png");
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("video/s3.wav", true);
    }
    else {
        UserDefault::getInstance()->setStringForKey("isBgMusic", "N");
        bgMusicBtn->loadTextureNormal("game/setting/bgMusicDisable.png");
        CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}

//调弦页定时开启 响应事件处理方法
void GameSetting::tuningBtnClick(Ref* pSender) {
    if ("N" == UserDefault::getInstance()->getStringForKey("isTuning")) {
        tuningBtn->loadTextureNormal("game/setting/tuningBtnEnable.png");
        UserDefault::getInstance()->setStringForKey("isTuning", "Y");
    }
    else {
        tuningBtn->loadTextureNormal("game/setting/tuningBtnDisable.png");
        UserDefault::getInstance()->setStringForKey("isTuning", "N");
    }
}

//获取吉他列表
void GameSetting::initGitarList() {
    bluetoolthTxt->setString("正在连接");
    
    auto load = Button::create("game/setting/bluetoothLoading.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    load->setPosition(Vec2(visibleSize.width / 2 - 130 - bluetoolthTxt->getContentSize().width, visibleSize.height / 2 - 80));
    this->addChild(load);
    
    auto repeate = RepeatForever::create(RotateBy::create(2, 180));
    load->runAction(repeate);
    
    //吉他列表  待修改为实际获取蓝牙设备列表
    for (int i = 0; i < 3; i++) {
        _gtararray.push_back(StringUtils::format("GTar%d", i));
    }
    
    //加载完删除等待控件
    this->removeChild(load, true);
    bluetoolthTxt->setString("选择吉他");
    
    for (int i = 0; i < _gtararray.size(); i++) {
        auto c_item = Text::create(_gtararray.at(i), "微软雅黑", 30);
        auto line_h = Button::create("game/setting/dividingLine.png");
        auto line_t = Button::create("game/setting/dividingLine.png");
        
        Layout* item = Layout::create();
        //item->setLayoutType(Layout::Type::VERTICAL);
        item->setSize(Size(100, 59));
        item->setTouchEnabled(true);
        if (i == 0) {
            line_h->setPosition(Vec2(0, item->getContentSize().height));
            item->addChild(line_h);
        }
        c_item->setPosition(Vec2(item->getContentSize().width - 20, item->getContentSize().height / 2));
        item->addChild(c_item);
        line_t->setPosition(Vec2(0, 0));
        item->addChild(line_t);
        //item->setBackGroundImage("game/setting/startTuningBtn.png");
        
        bluelistView->pushBackCustomItem(item);
        
    }
    bluelistView->setTouchEnabled(true);
    bluelistView->setVisible(true);
    bluelistView->addEventListenerListView(this, listvieweventselector(GameSetting::selectedItemEvent));
    
    
}

//连接蓝牙
bool GameSetting::connectBlooth() {
    return true;
}


void GameSetting::selectedItemEvent(cocos2d::Ref *pSender, ListViewEventType type)
{
    
    switch (type) {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            log("%ld", listView->getCurSelectedIndex());
        }
            break;
            
            
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            log("%ld", listView->getCurSelectedIndex());
            auto index = listView->getCurSelectedIndex();
            
            for (int i = 0; i < listView->getItems().size(); i++) {
                if (listView->getItems().at(i)->getChildByTag(100) != NULL) {
                    listView->getItems().at(i)->removeChildByTag(100);
                }
            }
            
            
            auto item = listView->getItem(listView->getCurSelectedIndex());
            auto load = Button::create("game/setting/Loading.png");
            load->setPosition(Vec2(20, item->getContentSize().height / 2));
            load->setTag(100);
            auto repeate = RepeatForever::create(RotateBy::create(2, 180));
            load->runAction(repeate);
            item->addChild(load);
            
            if (connectBlooth()) {
                listView->setVisible(false);
                auto conitem = item->clone(); 
                conitem->removeChildByTag(100);
                Size visibleSize = Director::getInstance()->getVisibleSize();
                auto tick = Button::create("game/setting/tick.png");
                tick->setPosition(Vec2(20, conitem->getContentSize().height / 2));
                
                if (index!=0) {
                    auto line_h = Button::create("game/setting/dividingLine.png");
                    line_h->setPosition(Vec2(0, conitem->getContentSize().height));
                    conitem->addChild(line_h);
                }
                
                conitem->addChild(tick);
                connBluelistView = ListView::create();
                connBluelistView->setSize(Size(248, 177));
                connBluelistView->setPosition(Vec2(visibleSize.width / 2 - 230, visibleSize.height / 2 - bluetoolthBtn->getContentSize().height - bluetoolthTxt->getContentSize().height - 177));
                connBluelistView->pushBackCustomItem(conitem);
                this->addChild(connBluelistView);
                bluetoolthTxt->setString("已连接");
            }
        }
            break;
        default:
            break;
    }
}