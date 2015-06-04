//
//  GameSettingLayer.h
//  poputar
//
//  Created by shigq on 15/6/1.
//
//

#ifndef __poputar__GameSettingLayer__
#define __poputar__GameSettingLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "MaskBaseLayer.h"

USING_NS_CC;
using namespace ui;

class GameSetting : public MaskBaseLayer {
    
private:
    Button* startTuningBtn;
    Button* bluetoolthBtn;
    Button* bgMusicBtn;
    Button* tuningBtn;
    ListView* bluelistView = NULL;
    ListView* connBluelistView = NULL;
    Text* bluetoolthTxt;
    std::vector<std::string>  _gtararray;//吉他列表
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    //ListView选择事件处理动作
    void selectedItemEvent(Ref *pSender, ListViewEventType type);
    
    //开始调弦按钮 响应事件处理方法
    void startTuningBtnClick(Ref* pSender);
    
    //蓝牙设备按钮 响应事件处理方法
    void bluetoolthBtnClick(Ref* pSender);
    
    //背景音按钮 响应事件处理方法
    void bgMusicBtnClick(Ref* pSender);
    
    //调弦页定时开启 响应事件处理方法
    void tuningBtnClick(Ref* pSender);
    
    //获取吉他列表
    void initGitarList();
    
    //连接蓝牙
    bool connectBlooth();
    
    //关闭调试也
    void closeBtnClick(Ref* ref);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameSetting);
};

#endif /* defined(__poputar__GameSettingLayer__) */
