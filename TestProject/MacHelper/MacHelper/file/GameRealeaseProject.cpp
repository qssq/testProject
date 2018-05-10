//
//  GameRealeaseProject.cpp
//  MacHelper
//
//  Created by gongxun on 2017/11/23.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "GameRealeaseProject.h"
#include <iostream>
#include "Defines.h"

GameRealeaseProject::GameRealeaseProject()
: mProjectPath("")
{
    
}

GameRealeaseProject::~GameRealeaseProject()
{
    
}

void GameRealeaseProject::start(const string &projectPath)
{
    mProjectPath = projectPath;
    
    //清除资源步骤
    //TODO
    fileHelper.removeFile("src/");
    fileHelper.removeFile(mProjectPath + "/publish/");
    
    //复制资源文件
    moveRes();
    
    //复制脚本文件
    moveSrc();
}

void GameRealeaseProject::moveRes()
{
    fileHelper.copyDirectory(mProjectPath + "/res", mProjectPath + "/publish/res");
    cout<<"复制文件夹完成:" + mProjectPath + "/res"<<endl;
}

void GameRealeaseProject::moveSrc()
{
    //去掉所有换行符
    //配置所有可以合并的目录
    //添加过滤文件
    fileHelper.createDir("src");

    vector<string> files = fileHelper.getDirectoryFile(mProjectPath + "/src");
    sort(files.begin(), files.end());
    
    vector<string> dirs = fileHelper.getDirectorys(mProjectPath + "/src");
    dirs.push_back(mProjectPath + "/src");
    sort(dirs.begin(), dirs.end());
//    for (int i = 0; i < dirs.size(); ++i)
//    {
//        cout<<"i:"<<i<<" name:"<<dirs[i]<<endl;
//    }
    
    //排除在外的文件
    vector<string> filterFiles =
    {
        "gameVersion.js",
        "gameAssetsManager.js",
        "gameHelper.js",
        "zVersion.js",
        "files.js",
        "resource.js"
    };
    fileHelper.copyFile(mProjectPath + "/src/gameVersion.js", mProjectPath + "/publish/src/gameVersion.js");
    fileHelper.copyFile(mProjectPath + "/src/gameAssetsManager.js", mProjectPath + "/publish/src/gameAssetsManager.js");
    fileHelper.copyFile(mProjectPath + "/src/tools/gameHelper.js", mProjectPath + "/publish/src/gameHelper.js");
    fileHelper.copyFile(mProjectPath + "/src/tools/zVersion.js", mProjectPath + "/publish/src/tools/zVersion.js");
    fileHelper.copyFile(mProjectPath + "/src/files.js", mProjectPath + "/publish/src/files.js");
    fileHelper.copyFile(mProjectPath + "/src/resource.js", mProjectPath + "/publish/src/resource.js");
    
    //开始合并
    for (int i = 0; i < dirs.size(); ++i)
    {
        string dir = dirs[i];
        
        //写入的临时文件
        ofstream ofile;
        string name = "src/" + getOnlyMarkedForVersion(i) + ".js";
        ofile.open(name, ios::binary | ios::trunc);
        ofile<<"//Created by MacHelper on "<<getCurDateTime()<<endl;
        
        //需要合并的文件
        vector<string> files = fileHelper.getDirectoryOnlyFile(dir);
        sort(files.begin(), files.end());
        for (string &filename : files)
        {
            //过滤隐藏文件
            string ssName = fileHelper.getFileName(filename);
            if (!getFilterFile(filename, filterFiles))
            {
                continue;
            }
            
            ifstream ifile;
            ifile.open(filename, ios::binary);
            string temp;
            while (!ifile.eof()) {
                getline(ifile, temp, '\n');
                
                string outStr;
                //过滤文件
                if (getFilterStr(temp, ssName, outStr))
                {
                    ofile<<outStr<<endl;
                }
            }
            ifile.close();
            
            ofile<<endl;
            ofile<<endl;
        }
        ofile.close();
        cout<<"i:"<<name<<" 合并" + dir + "文件 完成"<<endl;
    }
    
    fileHelper.copyDirectory("src", mProjectPath + "/publish/src");
    cout<<"复制文件夹完成: src"<<endl;
}

bool GameRealeaseProject::getFilterStr(const string &str, const string &fileName, string &outStr)
{
    outStr = str;
    
    if (fileName == "gameConfig.js")
    {
        string key = "that.isRelease = false";
        auto findIndex = outStr.find(key);
        if (findIndex != string::npos)
        {
            outStr.replace(findIndex, key.size(), "that.isRelease = true");
        }
    }
    
    return true;
}

bool GameRealeaseProject::getFilterFile(const string &fileName, const vector<string> &files)
{
    string ssName = fileHelper.getFileName(fileName);
    
    if (ssName[0] == '.')
    {
        return false;
    }
    
    for (auto i = 0; i < files.size(); ++i)
    {
        string testStr = files[i];
        if (ssName == testStr)
        {
            return false;
        }
    }
    
    return true;
}

string GameRealeaseProject::getOnlyMarkedForVersion(int index)
{
    int tempInt = index;
    int len = 26;
    vector<char> codes;
    for (int i = 0; i < len; i++) {
        char ascii = (i + 97);
        codes.push_back(ascii);
    }
    
    string result = "";
    char tempCharArray[10];
    sprintf(tempCharArray, "%c%c", codes[tempInt / len], codes[tempInt % len]);
    result = tempCharArray;
    return result;
}


















