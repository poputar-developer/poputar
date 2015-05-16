//
//  BLEScene.h
//  Guitars
//  蓝牙连接界面
//  Created by allen on 15-3-17.
//
//

#ifndef __Guitars__BLEScene__
#define __Guitars__BLEScene__

USING_NS_CC;
using namespace std;


class BLEScene : public Layer{
private:
    //连接蓝牙
    void connectBle(float dt);
    //跳转到下一个场景
    void nextSence(float dt);
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(BLEScene);
};

#endif /* defined(__Guitars__BLEScene__) */
