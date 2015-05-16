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

string POPTHelper::intToTime(int value_int){
    int minute = value_int/60;
    int sec = value_int%60;
    string minute_str = minute>=10 ? StringUtils::format("%d",minute): StringUtils::format("0%d",minute);
    string sec_str=sec>=10 ? StringUtils::format("%d",sec) : StringUtils::format("0%d",sec);
    string time_str = minute_str+":"+sec_str;
    return time_str;
}