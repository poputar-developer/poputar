//
//  POPTStringUtils.h
//  poputar 字符串帮助类
//  Created by allen on 15-3-27.
//
//

#ifndef __poputar__POPTStringUtils__
#define __poputar__POPTStringUtils__

#include <stdio.h>
using namespace std;

class POPTStringUtils{
public:
    //字符串根据pattern截取
    static vector<string> split(string str,string pattern);
    
    static string intToString(int value);
    
    static int stringToInt(string value);
};

#endif /* defined(__poputar__POPTStringUtils__) */
