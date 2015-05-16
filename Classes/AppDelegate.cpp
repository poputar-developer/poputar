#include "AppDelegate.h"
#include "BLEScene.h"
#include "PluginHelper.h"
#include "GameLevelScene.h"
//#include "SelectMusic.h"


USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
//    Size designSize=Size(960,640);
//    glview->setDesignResolutionSize(designSize.width, designSize.height,kResolutionExactFit);
    if(!glview) {
        glview = GLViewImpl::create("POPUTAR");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    //1 获得屏幕大小
    auto screenSize = glview ->getFrameSize();
    //2 设计大小
    auto designSize = Size(480,320);
    //3 资源大小
//    auto resourceSize = Size(480,320);
    
    std::vector<std::string> searchPaths;

    
    float proportion = screenSize.width/screenSize.height;
    
    if(proportion>=1.3 && proportion<1.4){
        searchPaths.push_back("pad");
        designSize = Size(1024 ,768);
    }else if(proportion>=1.5 && proportion<1.6){
        searchPaths.push_back("sd");
        designSize = Size(960, 640);
    }else if(proportion>=1.7 && proportion<1.8){
        searchPaths.push_back("hd");
        designSize = Size(1334 ,750);
    }
    searchPaths.push_back("base");

    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
  
//    if(screenSize.width>960){
//        designSize = Size(1334 ,750);
//        resourceSize = Size(1334,750);
//        //searchPaths.push_back("hd6");
//    }else if(screenSize.width>640){
//        designSize = Size(960, 640);
//        resourceSize = Size(960, 640);
//        //searchPaths.push_back("hd6");
//    }else{
//        //searchPaths.push_back("sd");
//    }
//    director->setContentScaleFactor(resourceSize.width/designSize.width);
//    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
    
    
    
    //蓝牙初始化
    PluginHelper::init();
    //蓝牙连接场景
    

//    auto scene = BLEScene::createScene();
    auto scene = GameLevel::createScene();
    
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
