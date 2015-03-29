//
//  POPTHelper.cpp
//  poputar
//
//  Created by allen on 15-3-28.
//
//

#include "POPTHelper.h"
long POPTHelper::getCurrentTime(){
    struct timeval now;
    gettimeofday(&now, NULL);
    long current = now.tv_sec *1000 + now.tv_usec /1000;
    return current;
}