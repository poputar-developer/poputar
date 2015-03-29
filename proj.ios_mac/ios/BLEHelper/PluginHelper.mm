//
//  PluginHelper.m
//  poputar
//
//  Created by allen on 15-3-15.
//
//

#import <UIKit/UIKit.h>
#import "BlueToothHelper.h"
#import "PluginHelper.h"


static BlueToothHelper *btHelper;
void PluginHelper::init(){
    btHelper = [BlueToothHelper shareManager];
    [btHelper didLoad];
    
}

void PluginHelper::scanBLEPeripherals(){
    [btHelper scanPeripherals];
}

void* PluginHelper::getBlueToothHelper(){
    return btHelper;
}


void PluginHelper::sendDate(unsigned char dataInfo[]){
    [btHelper sendData:(dataInfo)];
}

bool PluginHelper::isConnected(){
    return [btHelper isConnected];
}