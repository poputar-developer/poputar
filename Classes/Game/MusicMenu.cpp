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
    speedBase = 1;
    
    float maxWidthFlag = 0;
    float maxheightFlag = 0;

    
    //===================================主音控制=======================================
    string musicalStr = "主  音：";
    auto musicalLabel = Label::createWithTTF(musicalStr, "fonts/yuanti.ttf", 15);
    float musicalLabelWidth = musicalLabel->getContentSize().width;
    float musicalLabelHeight = musicalLabel->getContentSize().height/2;
    musicalLabel->setPosition(musicalLabelWidth/2+20,musicalLabelHeight+20);
    this->addChild(musicalLabel);
    
    auto musicalSwitch = ControlSwitch::create
    (Sprite::create("switch-mask.png"),
     Sprite::create("switch-on.png"),
     Sprite::create("switch-off.png"),
     Sprite::create("switch-thumb.png"),
     Label::createWithTTF("开", "fonts/manhuati.ttf", 15),
     Label::createWithTTF("关", "fonts/manhuati.ttf", 15));
    musicalSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(MusicMenu::musicalPlayController), Control::EventType::VALUE_CHANGED);
    float musicalSwitchWidth = musicalSwitch->getContentSize().width;
    musicalSwitch->setPosition(Vec2(musicalLabelWidth+musicalSwitchWidth/2+20,musicalLabelHeight+20));
    this->addChild(musicalSwitch);
    
    maxWidthFlag=musicalLabelWidth+20+musicalSwitchWidth;
    maxheightFlag+=musicalLabelHeight+20;
    
    //===================================节拍器控制=======================================
    string metronomeStr = "节拍器：";
    auto metronomeLabel = Label::createWithTTF(metronomeStr, "fonts/yuanti.ttf", 15);
    float metronomeLabelWidth = metronomeLabel->getContentSize().width;
    float metronomeLabelHeight = metronomeLabel->getContentSize().height/2;
    metronomeLabel->setPosition(metronomeLabelWidth/2+20,maxheightFlag+metronomeLabelHeight+20);
    this->addChild(metronomeLabel);
    
    auto metronomeSwitch = ControlSwitch::create
    (Sprite::create("switch-mask.png"),
     Sprite::create("switch-on.png"),
     Sprite::create("switch-off.png"),
     Sprite::create("switch-thumb.png"),
     Label::createWithTTF("开", "fonts/manhuati.ttf", 15),
     Label::createWithTTF("关", "fonts/manhuati.ttf", 15));
    metronomeSwitch->addTargetWithActionForControlEvents(this, cccontrol_selector(MusicMenu::metronomePlayController), Control::EventType::VALUE_CHANGED);
    float metronomeSwitchWidth = metronomeSwitch->getContentSize().width;
    metronomeSwitch->setPosition(Vec2(metronomeLabelWidth+metronomeSwitchWidth/2+20,maxheightFlag+metronomeLabelHeight+20));
    this->addChild(metronomeSwitch);
    
    float rowWidth =metronomeLabelWidth+20+metronomeSwitchWidth;
    maxWidthFlag = maxWidthFlag>rowWidth ? maxWidthFlag : rowWidth;
    maxheightFlag +=metronomeLabelHeight+20;
    
    //===================================速度控制=======================================
    string speedStr = "速  度：";
    auto speedLabel = Label::createWithTTF(speedStr, "fonts/yuanti.ttf", 15);
    float speedLabellWidth = speedLabel->getContentSize().width;
    float speedLabelHeight = speedLabel->getContentSize().height;
    speedLabel->setPosition(speedLabellWidth/2+20,maxheightFlag+speedLabelHeight/2+20);
    this->addChild(speedLabel);
    
    rowWidth = speedLabellWidth;
    
    ui::Button *speedDownBtn = ui::Button::create("minus.png");
    float speedDownBtnWidth = speedDownBtn->getContentSize().width;
    speedDownBtn->setPosition(Vec2(rowWidth+speedDownBtnWidth/2+20,maxheightFlag+speedLabelHeight/2+20));
    speedDownBtn->setScale(0.8);
    this->addChild(speedDownBtn);
    
    rowWidth+=speedDownBtnWidth;
    
    
    auto speedFlagLabel = Label::createWithTTF("X1.0", "fonts/yuanti.ttf", 15);
    float speedFlagLabelWidth = speedFlagLabel->getContentSize().width;
    speedFlagLabel->setPosition(rowWidth+speedFlagLabelWidth/2+20,maxheightFlag+speedLabelHeight/2+20);
    this->addChild(speedFlagLabel);
    
    rowWidth+=speedFlagLabelWidth;
    
    ui::Button *speedUpBtn = ui::Button::create("plus.png");
    float speedUpBtnBtnWidth = speedUpBtn->getContentSize().width;
    speedUpBtn->setPosition(Vec2(rowWidth+speedUpBtnBtnWidth/2+20,maxheightFlag+speedLabelHeight/2+20));
    speedUpBtn->setScale(0.8);
    this->addChild(speedUpBtn);

    speedUpBtn->addClickEventListener(CC_CALLBACK_1(MusicMenu::speedChangeController, this,true,speedFlagLabel));
    speedDownBtn->addClickEventListener(CC_CALLBACK_1(MusicMenu::speedChangeController, this,false,speedFlagLabel));
    
    
    rowWidth+=speedUpBtnBtnWidth;
    
    maxWidthFlag = maxWidthFlag>rowWidth ? maxWidthFlag : rowWidth;
    maxheightFlag+=speedLabelHeight+20;
    
    this->setPreferredSize(Size(maxWidthFlag+40,maxheightFlag+20));
}

void MusicMenu::setDelegate(MusicMenuDelegate *delegate){
    _delegate = delegate;
}

void MusicMenu::speedChangeController(cocos2d::Ref *ref,bool isSpeedUp,Label* speedFlagLabel){
    
    if(isSpeedUp){
        speedBase = speedBase>1.9 ? 2 : speedBase+0.1;
    }else{
        speedBase = speedBase<0.1 ? 0 : speedBase-0.1;
    }

    _delegate->speedChangeCallback(speedBase);
    
    speedFlagLabel->setString("X"+StringUtils::format("%.1f",speedBase));
    
}

void MusicMenu::metronomePlayController(cocos2d::Ref *ref,Control::EventType type){
    ControlSwitch* pSwitch = (ControlSwitch*)ref;
    _delegate->metronomePlayCallback(pSwitch->isOn());
}

void MusicMenu::musicalPlayController(cocos2d::Ref *ref,Control::EventType type){
    ControlSwitch* pSwitch = (ControlSwitch*)ref;
    _delegate->musicalPlayCallback(pSwitch->isOn());
}
