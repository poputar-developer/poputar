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
#include "Common.h"
//#include "GameLevelMenuItem.h"

Scene* GameLevel::createScene()
{
    auto scene = Scene::create();	
    auto layer = GameLevel::create();
    layer->loadFrame();
    scene->addChild(layer);
    return scene;
}


void GameLevel::loadFrame(){
 
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    float innerHeight = visibleSize.height *3;
    
    Size contentSize =  Size(visibleSize.width,innerHeight);
    auto scrollView = ui::ScrollView::create();
    scrollView->setAnchorPoint(Vec2(0,0));
    scrollView->setContentSize(visibleSize);
    scrollView->setInnerContainerSize(contentSize);
    scrollView->setPosition(Vec2(0,0));
    this->addChild(scrollView);
    
    
    auto bg = Sprite::create("background.png");
    bg->setScale(3);
    bg->setAnchorPoint(Vec2(0,0));
    bg->setPosition(Vec2(0, 0 ));
    scrollView->addChild(bg,0);
    
    

    ValueMapIntKey level;
    level[1]  = Value(3);
    level[2]  = Value(5);
    level[3]  = Value(10);

    
    

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
    
    //列的y坐标
    float menuY =innerHeight;
    
    for (int n=0; n<level.size(); n++) {
        int itemCount = level[n+1].asInt();
    
        int colCount = itemCount/itemCol;
        if(itemCount%itemCol>0){
            colCount+=1;
        }
        
        //根据行数计算总行高
        columnHeight = itemSide*colCount +itemSpace*(colCount-1);
            
        int xCount=0;
        float y = columnHeight-itemSide;
        
        Vector<MenuItem *> menuItems;
        for (int i=0; i<itemCount; i++) {
            if(xCount>itemCol-1){
                xCount = 0;
                y -=itemSide+itemSpace;
            }
            float x = xCount * (itemSide+itemSpace);
            auto ln = GameLevelMenuItem::createGameLevelMenuItem(false,n+1, i+1,CC_CALLBACK_1(GameLevel::toPlaySence, this));
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
        
        auto *bj = ui::Scale9Sprite::create("bj_t_gamelevel.png");
        bj->setPreferredSize(Size(columnWidth+bjMoreWidthSize*2, columnHeight+bjMoreHeightSize*2+bjGameLevelFlag));
        bj->setPosition(startX-bjMoreWidthSize, menuY-bjMoreHeightSize);
        bj->setAnchorPoint(Vec2::ZERO);
        scrollView->addChild(bj,0);
        
        string text = StringUtils::format("第%d阶段",n+1);
        auto label = Label::createWithBMFont("fonts/gamelevel.fnt", text);
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

void GameLevel::toPlaySence(Ref* sender){
    
    MusicInfo *musicInfo = MusicInfo::initWithJson("cunzai");
    Scene *guitarRunScene = GuitarRun::createScene(musicInfo);
//    auto transition = TransitionCrossFade::create(0.5f, guitarRunScene);
    Director::getInstance()->pushScene(guitarRunScene);
    
}


void GameLevel::setBackground(){
    log("back is empty");
}



