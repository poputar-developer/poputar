//
//  POPTGlobal.cpp
//  poputar
//
//  Created by allen on 15-4-14.
//
//

#include "POPTGlobal.h"
DECLARE_SINGLETON_MEMBER(POPTGlobal);
POPTGlobal::POPTGlobal(void){
    
}

POPTGlobal::~POPTGlobal(void){
    CC_SAFE_DELETE(gni);
    CC_SAFE_DELETE(runLayer);
    gni = NULL;
    runLayer = NULL;
}