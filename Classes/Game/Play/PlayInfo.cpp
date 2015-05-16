//
//  PlayInfo.cpp
//  poputar
//
//  Created by allen on 15-5-14.
//
//

#include "PlayInfo.h"

float PlayInfo::strToY(int str){
    
    int yFlag =0;
    switch (str) {
        case 1:
            yFlag = 6;
            break;
        case 2:
            yFlag = 5;
            break;
        case 3:
            yFlag = 4;
            break;
        case 4:
            yFlag = 3;
            break;
        case 5:
            yFlag = 2;
            break;
        case 6:
            yFlag = 1;
            break;
        default:
            break;
    }
    
    return config->stringSideHeight+config->stringUnitHeight*(float)(yFlag-1);
}