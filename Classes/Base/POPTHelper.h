//
//  POPTHelper.h
//  poputar
//
//  Created by allen on 15-3-28.
//
//

#ifndef __poputar__POPTHelper__
#define __poputar__POPTHelper__

#include <stdio.h>
USING_NS_CC;
using namespace std;
class POPTHelper{
public:
    //获得当前系统时间
    static long getCurrentTime();
    //将int转换成时间格式字符串
    static string intToTime(int time_now);
    
};

#endif /* defined(__poputar__POPTHelper__) */
