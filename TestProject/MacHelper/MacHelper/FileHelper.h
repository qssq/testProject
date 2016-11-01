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
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace std;
namespace fs = boost::filesystem;

class FileHelper
{
public:
    FileHelper();
    ~FileHelper();
    
    void showFileInfo(const string &file);
    void testOutFile();
    
    //获取目录里的所有文件
    vector<string> getDirectoryFile(const string &path);
    
    //复制文件
    void copyFile(const string &fromFile, const string &toFile);
private:
    string getKeyOrValue(const string &key, const string &value);
    
    void getFileForDirectory(const string &path, vector<string> &fileNames);
};

#endif /* defined(__MacHelper__FileHelper__) */
