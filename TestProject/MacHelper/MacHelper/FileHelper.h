//
//  FileHelper.h
//  MacHelper
//
//  Created by gongxun on 15/8/4.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacHelper__FileHelper__
#define __MacHelper__FileHelper__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

class FileHelper
{
public:
    FileHelper();
    ~FileHelper();
    
    void showFileInfo(const string &file);
};

#endif /* defined(__MacHelper__FileHelper__) */
