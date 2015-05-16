//
//  GuitarRunScene.cpp
//  Guitar
//
//  Created by allen on 14-11-30.
//
//

#include "GameRunScene.h"
#include "POPTGlobal.h"
#include "PlayRunLayer.h"
#include "POPTStringUtils.h"

#define LAYER_NUM_BACKGROUND 1
#define LAYER_NUM_MAIN 2
#define LAYER_NUM_MASK 3

//创建场景
Scene *GuitarRun::createScene(){
    auto scene=Scene::create();
    auto layer = GuitarRun::create();

    //初始化参数
    layer->initialise();
    //初始化游戏界面
    layer->loadGameFrame();
    //加载界面顶部内容
    layer->loadTopFrame();
    //加载界面底部内容
    layer->loadFootFrame();
    //开始动画
    layer->startAnimation();
    
    scene->addChild(layer);
    
    return scene;
}



//初始化
void GuitarRun::initialise(){
    
    this->setBackground();
    //节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("game/base/snare.caf");
    for (int i=1; i<8; i++) {
        string scaleFileName ="audio/scale/"+POPTStringUtils::intToString(i)+".mp3";
        CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(scaleFileName.c_str());
    }
    isPause =false;
    time_now = 0.0f;
}

void GuitarRun::loadGameFrame(){
    auto musicModel = poptGlobal->gni->getMusicModel();
    auto runLayer = startFingerMusic(musicModel,visibleSize.height-topSideHeight-footSideHeight);
    runLayer->setName("runLayer");
    addChild(runLayer,LAYER_NUM_MAIN);
    poptGlobal->runLayer = runLayer;
}

//加载头部组件
void GuitarRun::loadTopFrame(){
    auto musicModel = poptGlobal->gni->getMusicModel();
    string title= musicModel->getTitle();
    float height = topSideHeight;
    //返回按钮
    auto backBtn = ui::Button::create("game/base/back.png");
    backBtn->setPosition(Vec2(50, visibleSize.height-height/2));
    backBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::goBack, this));
    this->addChild(backBtn,LAYER_NUM_MAIN);
    
    //设置歌曲名
    auto label = Label::createWithTTF(title, "fonts/yuanti.ttf", 36);
    label->setPosition(150,visibleSize.height-height/2);
    this->addChild(label,LAYER_NUM_MAIN);
    

    auto auditionBtn = ui::Button::create();
    auditionBtn->setTitleFontSize(32);
    auditionBtn->setTitleText("试 听");
    auditionBtn->setPosition(Vec2(visibleSize.width-100, visibleSize.height-height/2));
    auditionBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::auditionControll,this));
    this->addChild(auditionBtn,LAYER_NUM_MAIN);

}

//加载底部组件
void GuitarRun::loadFootFrame(){
    float height=footSideHeight;
    //暂停
    pauseBtn = ui::Button::create("game/base/pause.png");
    pauseBtn->addClickEventListener(CC_CALLBACK_1(GuitarRun::pauseControll, this));
    pauseBtn->setPosition(Vec2(50,height/2));
    this->addChild(pauseBtn,LAYER_NUM_MAIN);
    
    //时间信息
    float allTime = poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime;
    int value_int = ceil(allTime);
    string time_str = POPTHelper::intToTime(value_int);
    string text = "00:00\\"+time_str;
    time = Label::createWithTTF(text, "fonts/yuanti.ttf", 24);
    time->setColor(Color3B::WHITE);
    time->setPosition(visibleSize.width-150,height/2);
    this->addChild(time,LAYER_NUM_MAIN);
    
    //重新开始按钮
    restartBtn = ui::Button::create("game/base/restart.png");
    restartBtn->setPosition(Vec2(visibleSize.width-50,height/2));
    restartBtn->addClickEventListener(CC_CALLBACK_0(GuitarRun::endRestartCallback,this));
    this->addChild(restartBtn,LAYER_NUM_MAIN);
    
}

//移动时间轴定时任务的方法
void GuitarRun::moveTime(float at){
    time_now+=1;
    string text = time->getString();
    vector<string> timeInfos =POPTStringUtils::split(text, "\\");
    int value_int = ceil(time_now);
    timeInfos[0] = POPTHelper::intToTime(value_int);
    time->setString(timeInfos[0]+"\\"+timeInfos[1]);
    
    float allTime = poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime;
    //歌曲结束
    if(time_now >= allTime){
        //通知和弦关闭
        __Bool* chordVoice = __Bool::create(false);
        __NotificationCenter::getInstance()->postNotification(POPT_CHORD_VOICE,chordVoice);
        //通知主音关闭
        __Bool* toincVoice = __Bool::create(false);
        __NotificationCenter::getInstance()->postNotification(POPT_TOINC_VOICE,toincVoice);
        //通知节拍器关闭
        __Bool* metronomeVoice = __Bool::create(false);
        __NotificationCenter::getInstance()->postNotification(POPT_METRONOME_VOICE,metronomeVoice);
        

        
        //更新关卡信息
        //系统等级
        int curr_level = UserDefault::getInstance()->getIntegerForKey(CURR_LEVEL_KEY);
        //系统节点
        int curr_node = UserDefault::getInstance()->getIntegerForKey(CURR_NODE_KEY);
        
        //游戏等级
        int gameLevel =poptGlobal->gni->getGameLevelInfo()->getLevel();
        //游戏节点
        int gameNode = poptGlobal->gni->getNode();
        
        vector<GameLevelInfo*> levels = gameLevelSingleton->levels;
        
        GameLevelInfo* curr_gli = levels[gameLevel-1];
        vector<GameNodeInfo*> nodes = curr_gli->getNodes();
        
        if(gameNode == curr_node && gameLevel == curr_level){
            if(gameNode+1<=nodes.size()){
                //过关
                UserDefault::getInstance()->setIntegerForKey(CURR_NODE_KEY, gameNode+1);
            }else if(gameLevel+1<=levels.size()){
                //通过阶段
                UserDefault::getInstance()->setIntegerForKey(CURR_LEVEL_KEY, gameLevel+1);
                UserDefault::getInstance()->setIntegerForKey(CURR_NODE_KEY, 1);
            }
        }
        
        
        log("关卡结束");
        unschedule(schedule_selector(GuitarRun::moveTime));
        EndLayer* endLayer = EndLayer::createEndLayer();
        endLayer->setName("endLayer");
        endLayer->setDelegate(this);
        this->addChild(endLayer,99);
    }
}

void GuitarRun::auditionControll(cocos2d::Ref *ref){
    //暂停游戏
    if(!isPause){
        pauseGame();
    }
    
    auto musicModel = poptGlobal->gni->getMusicModel();
    float allTime = poptGlobal->runLayer->gameConfig->musicTime+poptGlobal->runLayer->gameConfig->endTime;
    auto auditionLayer= AuditionLayer::createAuditionLayer(musicModel->getTitle(),time_now,allTime);
    auditionLayer->setName("auditionLayer");
    auditionLayer->setDelegate(this);
    poptGlobal->runLayer->audition(true);
    this->addChild(auditionLayer,LAYER_NUM_MASK);
}

//游戏开始时的3秒动画
void GuitarRun::startAnimation(){

    auto layerColor = LayerColor::create(Color4B(0,0,0,200));
    
    auto countDown = CSLoader::createNode("game/base/Countdown.csb");
    countDown->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    
    auto action = CSLoader::createTimeline("game/base/Countdown.csb");
    action->gotoFrameAndPlay(0, false);
    countDown->runAction(action);
    layerColor->addChild(countDown);

    action->setFrameEventCallFunc([=](Frame* frame){
        EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
         if(!evnt)
             return;
         string str = evnt->getEvent();
         if(str == "End"){
             this->removeChild(layerColor);
             poptGlobal->runLayer->endAnimationSetting();
             schedule(schedule_selector(GuitarRun::moveTime), 1, kRepeatForever, 0.000001);
         }
     });

    this->addChild(layerColor,LAYER_NUM_MASK);

    
    //创建一个全屏的按钮，阻止触摸事件
    auto blackItem = MenuItem::create();
    blackItem->setPosition(visibleSize.width/2,visibleSize.height/2);
    blackItem->setContentSize(visibleSize);//设置大小为整个屏幕的大小
    
    auto blackMenu = Menu::create(blackItem,NULL);
    blackMenu->setPosition(Point::ZERO);
    blackMenu->setAnchorPoint(Point::ZERO);
    layerColor->addChild(blackMenu,100);

}

//暂停按钮
void GuitarRun::pauseControll(cocos2d::Ref *ref){
    log("pause controll");
//    ui::Button* btn= (ui::Button *)ref;
    if(!isPause){
        this->pauseGame();
    }else{
        this->resumeGame();
    }
    isPause = !isPause;
}

//暂停
void GuitarRun::pauseGame(){
    pauseBtn->loadTextureNormal("game/base/play.png");
    poptGlobal->runLayer->sectionPause();
    this->getScheduler()->pauseTarget(this);
}
//继续
void GuitarRun::resumeGame(){
    pauseBtn->loadTextureNormal("game/base/pause.png");
    poptGlobal->runLayer->sectionResume();
    this->getScheduler()->resumeTarget(this);
}


//开始指弹界面
RunLayer* GuitarRun::startFingerMusic(MusicModel *musicModel,float height){
    auto runLayer = PlayRunLayer::createPlayRunLayer(musicModel,height);
    return runLayer;
}

//设置背景
void GuitarRun::setBackground(){
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("game/base/background.png");
    sprite->setOpacity(200); //0-255
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ));
    
    this->addChild(sprite, LAYER_NUM_BACKGROUND);
}

//返回关卡界面
void GuitarRun::goBack(cocos2d::Ref *sender){
    if(poptGlobal->runLayer){
        poptGlobal->runLayer->stopMusic();
    }
    isPause =false;
    
    //去掉节拍声音
    CocosDenshion::SimpleAudioEngine::getInstance()->unloadEffect("game/base/snare.caf");
    poptGlobal->runLayer = nullptr;
    Director::getInstance()->popScene();
}


//结束层的“重新开始”按钮
void GuitarRun::endRestartCallback(){

    unschedule(schedule_selector(GuitarRun::moveTime));
    poptGlobal->runLayer->stopMusic();

    time_now = 0.0f;
    removeChildByName("runLayer");
    RunLayer* runLayer;
    auto musicModel = poptGlobal->gni->getMusicModel();
    runLayer = startFingerMusic(musicModel,visibleSize.height-topSideHeight-footSideHeight);
    runLayer->setName("runLayer");
    this->addChild(runLayer,LAYER_NUM_MAIN);

    poptGlobal->runLayer = runLayer;
    startAnimation();

    this->removeChildByName("endLayer");
}

//结束层的继续
void GuitarRun::endBackCallback(){
    this->removeChildByTag(2);
    resumeGame();
    pauseBtn->loadTextureNormal("game/base/pause.png");
    goBack(nullptr);
}

void GuitarRun::endNextCallback(){
    this->removeAllChildren();
    
    //得到下一关的node信息
    //阶段
    int curr_level = poptGlobal->gni->getNode();
    //小关
    int curr_node = poptGlobal->gni->getGameLevelInfo()->getLevel();
    
    vector<GameLevelInfo*> levels = gameLevelSingleton->levels;
    GameLevelInfo* gli = levels[curr_level-1];
    vector<GameNodeInfo*> nodes = gli->getNodes();
    //currentNodeIndex = (curr_node-1)   下一关 curr_node-1 + 1
    GameNodeInfo* gni = nodes[curr_node];
    //加载音乐信息
    string musicFile = "music/stage/"+POPTStringUtils::intToString(gni->getGameLevelInfo()->getLevel())+"/"+gni->getMusic();
    auto musicModel = MusicModel::initWithFile(musicFile);
    gni->setMusicModel(musicModel);
    poptGlobal->gni = gni;
    
    //初始化参数
    initialise();
    //初始化游戏界面
    loadGameFrame();
    //加载界面顶部内容
    loadTopFrame();
    //加载界面底部内容
    loadFootFrame();
    //开始动画
    startAnimation();
    
    this->removeChildByName("endLayer");
}


void GuitarRun::auditionBackCallback(cocos2d::Ref *ref){
    resumeGame();
    poptGlobal->runLayer->audition(false);
    this->removeChildByName("auditionLayer");
}



