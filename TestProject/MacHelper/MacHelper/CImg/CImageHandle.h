//
//  CImageHandle.hpp
//  MacHelper
//
//  Created by gongxun on 17/3/6.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef CImageHandle_hpp
#define CImageHandle_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <map>

using namespace std;

struct frameStruct
{
    string name;
    int x;
    int y;
    int w;
    int h;
    bool rotated;
};

class CImageHandle
{
public:
    CImageHandle();
    ~CImageHandle();
    
    void handler();
    void handlerKw();
private:
    string getFullName(const string &file);
    
    //裁切大文件
    void copyFiles(const vector<frameStruct> &rects, const string &file, const string &path);
    
    //特殊处理返回结构
    vector<frameStruct> getFrameStruct(const string &file);
};

#endif /* CImageHandle_hpp */
