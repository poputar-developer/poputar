//
//  POPTStringUtils.cpp
//  poputar
//
//  Created by allen on 15-3-27.
//
//

#include "POPTStringUtils.h"

vector<string> POPTStringUtils::split(string str, string pattern){
    string::size_type pos;
    vector<string> result;
    str+=pattern;//扩展字符串以方便操作
    int size=(int)str.size();
    

    for(int i=0; i<size; i++)
    {
        pos=str.find(pattern,i);
        if(pos<size)
        {
            string s=str.substr(i,pos-i);
            result.push_back(s);
            i=(int)(pos+pattern.size()-1);
        }
    }
    return result;
}