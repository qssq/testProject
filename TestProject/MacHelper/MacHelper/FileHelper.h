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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
namespace fs = boost::filesystem;

class FileHelper
{
public:
    static string gStartPath;
    static string gProjectName;
    FileHelper();
    ~FileHelper();
    
    void showFileInfo(const string &file);
    void testOutFile();
    
    //复制文件
    void copyFile(const string &fromFile, const string &toFile);
    
    //获取目录里的所有文件
    vector<string> getDirectoryFile(const string &path);
    
    //返回目录下面所有文件夹
    vector<string> getDirectory(const string &path);
    
    //返回文件名
    string getFileName(const string &path);
    
    //删除文件
    int removeFile(const string &path);
    
    //返回json文件
//    void getJSONFile(const string &fileName, boost::property_tree::ptree &outPtree);
private:
    string getKeyOrValue(const string &key, const string &value);
    
    void getFileForDirectory(const string &path, vector<string> &fileNames);
};

#endif /* defined(__MacHelper__FileHelper__) */
