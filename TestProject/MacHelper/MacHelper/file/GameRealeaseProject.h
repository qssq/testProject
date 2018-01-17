//
//  GameRealeaseProject.hpp
//  MacHelper
//
//  Created by gongxun on 2017/11/23.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef GameRealeaseProject_hpp
#define GameRealeaseProject_hpp

#include <stdio.h>
#include <string>
#include "FileHelper.h"

using namespace std;

class GameRealeaseProject
{
public:
    GameRealeaseProject();
    ~GameRealeaseProject();
    
    void start(const string &projectPath);
private:
    string mProjectPath;
    FileHelper fileHelper;
    
    void moveRes();
    void moveSrc();
    
    //过滤文件内容
    bool getFilterStr(const string &str, const string &fileName, string &outStr);
    
    //过滤文件
    bool getFilterFile(const string &fileName, const vector<string> &files);
    
    string getOnlyMarkedForVersion(int index);
};

#endif /* GameRealeaseProject_hpp */
