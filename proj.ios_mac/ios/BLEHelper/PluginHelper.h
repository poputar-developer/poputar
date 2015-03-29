//
//  PluginHelper.h
//  poputar
//
//  Created by allen on 15-3-15.
//
//  cocos2d-x调用ios api的桥梁类
//
using namespace std;

class PluginHelper{
    
public:
    //初始化蓝牙信息
    static void init();
    
    //扫描并连接
    static void scanBLEPeripherals();
    
    //static void connectPeripherals();
    
    static void sendDate(unsigned char dataInfo[]);

    static void* getBlueToothHelper();
    
    static bool isConnected();
    
};

