//
//  ZipDemo.hpp
//  MacHelper
//
//  Created by gongxun on 15/12/11.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#ifndef ZipDemo_h
#define ZipDemo_h

#include <stdio.h>
#include <string>

class ZipDemo
{
public:
    ZipDemo();
    ~ZipDemo();
    
    void compressFile(const std::string sourceFile, const std::string destFile);
    void uncpmpressFile(const std::string sourceFile, const std::string destFile);
};

#endif /* ZipDemo_hpp */
