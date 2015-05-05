//
//  Fingering.cpp
//  Guitars
//
//  Created by allen on 14-12-28.
//
//

#include "GameLevel.h"
#include "GameLevelMenuItem.h"
#include "MusicInfo.h"
#include "GuitarRunScene.h"
#include "StartScene.h"
#include "POPTGlobal.h"
#include "POPTStringUtils.h"
#include "MusicModel.h"

//#include "GameLevelMenuItem.h"

Scene* GameLevel::createScene()
{
    auto scene = Scene::create();	
    auto layer = GameLevel::create();
//    layer->loadFrame();
    scene->addChild(layer);
    return scene;
}


void GameLevel::loadFrame(){
 
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto scrollView = ui::ScrollView::create();
    scrollView->setAnchorPoint(Vec2(0,0));
    scrollView->setContentSize(visibleSize);
        scrollView->setPosition(Vec2(0,0));
    this->addChild(scrollView);
    
    
    auto bg = Sprite::create("base/background.png");
    bg->setScale(2);
    bg->setAnchorPoint(Vec2(0,0));
    bg->setPosition(Vec2(0, 0 ));
    scrollView->addChild(bg,0);

    
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

    

    //布局计算
    //获得屏幕尺寸
    float width = visibleSize.width;
    //关卡meunItem大小
    float itemSide = 57.0f;
    //关卡间隔
    float itemSpace = 20.0f;
    //每拍关卡个数
    int itemCol = 4;
    //整个行的宽度
    float columnWidth =itemCol*itemSide + (itemCol-1)*itemSpace;
    //开始的x坐标（距离左侧的距离）
    float startX = (width - columnWidth)/2;
    //关卡行间距
    float columnSpace = 100.0f;
    //行高
    float columnHeight = 0.0f;
    vector<GameLevelInfo*> levels = gameLevelSingleton->levels;
    
    //计算页面高度
    float innerHeight = columnSpace;
    for (int l=0; l<levels.size(); l++) {
        GameLevelInfo* gli = levels[l];
        int itemCount = (int)gli->getNodes().size();
        
        int colCount = itemCount/itemCol;
        if(itemCount%itemCol>0){
            colCount+=1;
        }
        innerHeight += itemSide*colCount +itemSpace*(colCount-1) + columnSpace;
    }
    //设置scrollview大小
    Size contentSize =  Size(visibleSize.width,innerHeight);
    scrollView->setInnerContainerSize(contentSize);
    
    //列的y坐标计算使用
    float menuY =innerHeight;
    
    log("scrollview高度：%f",innerHeight);

    for (int l=0; l<levels.size(); l++) {
        GameLevelInfo *gli = levels[l];
        vector<GameNodeInfo*> nodes = gli->getNodes();
        int level = gli->getLevel();
        int itemCount = (int)nodes.size();
        
        int colCount = itemCount/itemCol;
        if(itemCount%itemCol>0){
            colCount+=1;
        }
        
        //根据行数计算总行高
        columnHeight = itemSide*colCount +itemSpace*(colCount-1);
        
        int xCount=0;
        float y = columnHeight-itemSide;
        
        Vector<MenuItem *> menuItems;
        for (int n=0; n<nodes.size(); n++) {
            GameNodeInfo* gni = nodes[n];
            
            string type =gni->getType();
            string music = gni->getMusic();
            int node = gni->getNode();
            
            

            
            if(xCount>itemCol-1){
                xCount = 0;
                y -=itemSide+itemSpace;
            }
            float x = xCount * (itemSide+itemSpace);
            
            bool isLock = true;
            if(curr_level>level){
                isLock = false;
            }else if(curr_level==level){
                if(curr_node>=node){
                    isLock = false;
                }
            }
            auto ln = GameLevelMenuItem::createGameLevelMenuItem(isLock,node,CC_CALLBACK_1(GameLevel::toPlaySence, this,gni));
            
            ln->setAnchorPoint(Vec2::ZERO);
            ln->setPosition(Vec2(x , y));
            
            menuItems.pushBack(ln);
            xCount++;
            
        }
    
        menuY = menuY - columnHeight - columnSpace;
        
        //背景上方关卡标志高度
        float bjGameLevelFlag = 25;
        //背景图片大出的大小
        float bjMoreWidthSize = 50;
        float bjMoreHeightSize = 25;
        
        auto *bj = ui::Scale9Sprite::create("level/bj_t_gamelevel.png");
        bj->setPreferredSize(Size(columnWidth+bjMoreWidthSize*2, columnHeight+bjMoreHeightSize*2+bjGameLevelFlag));
        bj->setPosition(startX-bjMoreWidthSize, menuY-bjMoreHeightSize);
        bj->setAnchorPoint(Vec2::ZERO);
        scrollView->addChild(bj,0);
        
        string text = StringUtils::format("第%d阶段",l+1);
        auto label = Label::createWithBMFont("fonts/gamelevel.fnt", text);
//        auto label =Label::createWithTTF(text, "fonts/manhuati.ttf",20);
        label->setAnchorPoint(Vec2::ZERO);
        label->setPosition(startX, menuY+columnHeight+bjMoreHeightSize*2-bjGameLevelFlag);
        scrollView->addChild(label,2);
        
        auto mu = Menu::createWithArray(menuItems);
        mu->setContentSize(Size(columnWidth, columnHeight));
        mu->setAnchorPoint(Vec2::ZERO);
        mu->setPosition(startX,menuY);
        scrollView->addChild(mu,1);
    }
}

void GameLevel::toPlaySence(Ref* sender,GameNodeInfo* gni){
    
    log("to level:%d  node:%d",gni->getGameLevelInfo()->getLevel(),gni->getNode());
    poptGlobal->gni = gni;
    string type = gni->getType();
    
    //加载音乐信息
    string musicFile = "music/stage/"+POPTStringUtils::intToString(gni->getGameLevelInfo()->getLevel())+"/"+gni->getMusic();
    
    
    bool test= true;
    if(test) {
        auto musicModel = MusicModel::initWithFile(musicFile);
        gni->setMusicModel(musicModel);
    }else{
        auto musicInfo = MusicInfo::initWithJson(musicFile);
        gni->setMusicInfo(musicInfo);

    }
    
    Scene* scene;
    if(type=="C"){
        scene = StartScene::createScene();
    }else if(type == "F"){
        scene = StartScene::createScene();
    }else if(type == "S"){
        scene = GuitarRun::createScene();
    }
    
    auto transition = TransitionCrossFade::create(0.5f, scene);
    Director::getInstance()->pushScene(transition);
}


void GameLevel::setBackground(){
    log("back is empty");
}




void GameLevel::onEnter(){
    Layer::onEnter();
    
    loadFrame();
}

