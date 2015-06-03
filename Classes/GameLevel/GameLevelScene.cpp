//
//  Fingering.cpp
//  Guitars
//
//  Created by allen on 14-12-28.
//
//


#include "../Base/POPTBaseDefine.h"



Scene* GameLevel::createScene()
{
    auto scene = Scene::create();	
    auto layer = GameLevel::create();
    scene->addChild(layer);
    return scene;
}

bool GameLevel::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("GameLevelCardHandlerReader",(ObjectFactory::Instance)GameLevelCardReader::getInstance);
    auto pageLayer = CSLoader::createNode("gameLevel/GameLevelCardLayer.csb");
    pageLayer->setContentSize(visibleSize);
    ui::Helper::doLayout(pageLayer);
    pv = (PageView*)pageLayer->getChildByName("PageView");
    pageLayer->setPosition(Vec2::ZERO);
    this->addChild(pageLayer);
    
    auto musicLibBtn = (ui::Button*)pageLayer->getChildByName("musicLibBtn");
    musicLibBtn->addClickEventListener(CC_CALLBACK_1(GameLevel::musicLibBtnController, this));
    
    auto settingBtn = (ui::Button*)pageLayer->getChildByName("settingBtn");
    settingBtn->addClickEventListener(CC_CALLBACK_1(GameLevel::settingBtnController, this));
    
    return true;
}

void GameLevel::musicLibBtnController(cocos2d::Ref *ref){
    auto musicLibScene = MusicLibScene::createScene();
    Director::getInstance()->pushScene(musicLibScene);
}

void GameLevel::settingBtnController(cocos2d::Ref *ref){
    auto settinglayer = GameSetting::create();
    this->addChild(settinglayer,2);
}

void GameLevel::onEnter(){
    
    Layer::onEnter();
    
    pv->removeAllPages();
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //得到当前关卡信息
    int curr_level = UserDefault::getInstance()->getIntegerForKey(CURR_LEVEL_KEY);
    int curr_node = UserDefault::getInstance()->getIntegerForKey(CURR_NODE_KEY);
    if(curr_level == 0){
        UserDefault::getInstance()->setIntegerForKey(CURR_LEVEL_KEY, 1);
        curr_level =1;
    }
    
    if(curr_node == 0){
        UserDefault::getInstance()->setIntegerForKey(CURR_NODE_KEY, 1);
        curr_node = 1;
    }
    vector<GameLevelInfo*> levels = gameLevelSingleton->levels;
    
    for (int i=0; i<levels.size(); i++) {
        auto layout = ui::Layout::create();
        Node* levelNode ;
        if(i+1<curr_level){
            levelNode = getLevelInfo(i+1, 8);
        }else if(i+1 == curr_level){
            levelNode= getLevelInfo(i+1, curr_node);
        }else if(i+1>curr_level){
            levelNode = getLevelInfo(i+1, 0);
        }
        levelNode->setPositionX(visibleSize.width/2);
        layout->addChild(levelNode);
        pv->addPage(layout);
    }
    //滚到到当前关卡
    pv->scrollToPage(curr_level-1);
}

Node* GameLevel::getLevelInfo(int levelIndex,int nodeIndex){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    vector<GameLevelInfo*> levels = gameLevelSingleton->levels;
    auto rootNode = CSLoader::createNode("gameLevel/GameLevelCard.csb");
    auto bgNode = rootNode->getChildByName("game_level_bg_1");
    
//    rootNode->setContentSize(visibleSize);
//    ui::Helper::doLayout(rootNode);
    GameLevelInfo* gli = levels[levelIndex-1];
    
    ui::Text* title = (ui::Text*)bgNode->getChildByName("Title");
    title->setString("Part "+POPTStringUtils::intToString(levelIndex)+" "+gli->getTitle());
    vector<GameNodeInfo*> nodes = gli->getNodes();
    //设置关卡信息。如果少于8小关，则隐藏多出的关卡
    for (int index = 1; index<=8; index++) {
        auto node = bgNode->getChildByName("node"+POPTStringUtils::intToString(index));
        if(index<=nodes.size()){
            node->setUserData(nodes[index-1]);
            ui::Button* btn = (ui::Button*)node;
            //设置按钮状态
            if(nodeIndex>=index){
                btn->setEnabled(true);
                btn->setBright(true);
                btn->setBrightStyle(BrightStyle::NORMAL);
            }
        }else{
            node->setVisible(false);
        }
    }

    rootNode->setPositionY(visibleSize.height/2);
    return rootNode;
}

void GameLevel::toPlaySence(Ref* sender,GameNodeInfo* gni){
    
    log("to level:%d  node:%d",gni->getGameLevelInfo()->getLevel(),gni->getNode());
    poptGlobal->gni = gni;
    
    //加载音乐信息
    string musicFile = "music/stage/"+POPTStringUtils::intToString(gni->getGameLevelInfo()->getLevel())+"/"+gni->getMusic();
    
    
    auto musicModel = MusicModel::initWithFile(musicFile);
    gni->setMusicModel(musicModel);
    
    Scene* scene = StartScene::createScene();
    
    auto transition = TransitionCrossFade::create(0.5f, scene);
    Director::getInstance()->pushScene(transition);
}


void GameLevel::setBackground(){
    log("back is empty");
}



