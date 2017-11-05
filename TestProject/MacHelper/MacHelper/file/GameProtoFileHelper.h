//
//  GameProtoFileHelper.hpp
//  MacHelper
//
//  Created by gongxun on 17/11/2.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef GameProtoFileHelper_hpp
#define GameProtoFileHelper_hpp

#include <stdio.h>
#include <string>

using namespace std;

class GameProtoFileHelper
{
public:
    GameProtoFileHelper();
    ~GameProtoFileHelper();
    
    void start(const string &protoDir, const string &projectDir);
    
private:
    string mBaseProtoName;
    bool mIsCommentedOuting;
    
    bool getFilterStr(const string &str, const string &fileName, string &outStr);
    void movoFile(const string &projectDir);
};

#endif /* GameProtoFileHelper_hpp */
