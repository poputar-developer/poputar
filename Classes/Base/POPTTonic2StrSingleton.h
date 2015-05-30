//
//  POPTTonic2Str.h
//  poputar
//
//  Created by allen on 15-5-20.
//
//

#ifndef __poputar__POPTTonic2StrSingleton__
#define __poputar__POPTTonic2StrSingleton__

#include <stdio.h>
#include "Singleton.h"
using namespace  std;
class POPTTonic2StrSingleton :public Singleton<POPTTonic2StrSingleton>{
private:
    map<string,string> tonic2StrMap;
public:
    
    POPTTonic2StrSingleton();
    
    ~POPTTonic2StrSingleton();
    //加载主音弦位信息
    void loadCurrentTonic(string type);
    
    void unLoadTonic();
    
    string getStrInfo(string note);
    
};

#define tonic2StrSingleton POPTTonic2StrSingleton::instance()

#endif /* defined(__poputar__POPTTonic2Str__) */
