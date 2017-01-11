//
//  GameGroupHelper.cpp
//  MacHelper
//
//  Created by gongxun on 16/11/1.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "GameGroupHelper.h"
#include "FileHelper.h"

#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std::chrono;

GameGroupHelper *GameGroupHelper::mGameGroupHelper = nullptr;

GameGroupHelper::GameGroupHelper()
{
    mProjectPath = "/Users/gongxun/oschina/gt_sphere/mobiles/GameGroup/";
    mProjectVersion = "0018";
}

GameGroupHelper::~GameGroupHelper()
{
    
}

GameGroupHelper *GameGroupHelper::singleton()
{
    if (!mGameGroupHelper)
    {
        mGameGroupHelper = new GameGroupHelper();
    }
    return mGameGroupHelper;
}

void GameGroupHelper::buildConfigFile()
{
    vector<string> srcs = {
        "/Users/gongxun/oschina/gt_sphere/mobiles/GameGroup/src/"
    };
    
    vector<string> ress = {
        "/Users/gongxun/oschina/gt_sphere/mobiles/GameGroup/res/"
    };
    
    buildConfig(srcs, ress, mProjectPath);
}

void GameGroupHelper::buildConfigKwxFile()
{
    vector<string> srcs = {
        "/Users/gongxun/oschina/gt-card/mobiles/GTKwx/src/"
    };
    
    vector<string> ress = {
        "/Users/gongxun/oschina/gt-card/mobiles/GTKwx/res/"
    };
    
    buildConfig(srcs, ress, "/Users/gongxun/oschina/gt-card/mobiles/GTKwx/");
}

void GameGroupHelper::buildHtmlTest()
{
    FileHelper fileHelper;
    //复制文件
    string otPath = "/Users/gongxun/Sites/group/";
    //需要复制的文件
    vector<string> fileNames;
    for (fs::directory_entry& x : fs::directory_iterator(mProjectPath))
    {
        fs::path p = x.path();
        if (fs::is_regular_file(p))
        {
            fileNames.push_back(p.string());
        }
        else if (fs::is_directory(p))
        {
            if (p.filename().string() != "cocostudio" && p.filename().string() != "frameworks")
            {
                vector<string> temp = fileHelper.getDirectoryFile(p.string());
                fileNames.insert(fileNames.end(), temp.begin(), temp.end());
            }
        }
    }
    //过滤文件
    for (auto it = fileNames.begin(); it != fileNames.end(); )
    {
        fs::path p(*it);
        if (p.filename().string().front() == '.')
        {
            it = fileNames.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    //复制到的文件
    vector<string> toFileNames;
    for (int i = 0; i < fileNames.size(); ++i)
    {
        string newFileName = otPath + fileNames[i].substr(mProjectPath.size());
        toFileNames.push_back(getRenameJsFile(newFileName));
    }
    
    cout<<"------------------------"<<endl;
    cout<<"------------------------"<<endl;
    
    for (int i = 0; i < fileNames.size(); ++i)
    {
        fileHelper.copyFile(fileNames[i], toFileNames[i]);
    }
    
    
//    buildConfig("/Users/gongxun/Sites/group/src/", "/Users/gongxun/Sites/group/res/", otPath);
//    buildConfig("/Users/gongxun/Sites/group/hallSrc/", "/Users/gongxun/Sites/group/hallRes/", otPath);
//    buildConfig("/Users/gongxun/Sites/group/gameKwx/src/", "/Users/gongxun/Sites/group/gameKwx/res/", otPath);
}

void GameGroupHelper::buildHtmlKwxTest()
{
    FileHelper fileHelper;
    //复制文件
    string otPath = "/Users/gongxun/Sites/kwx/";
    //本地文件位置
    string mLocationPath = "/Users/gongxun/oschina/gt-card/mobiles/GTKwx";
    
    //需要复制的文件
    vector<string> fileNames;
    for (fs::directory_entry& x : fs::directory_iterator(mLocationPath))
    {
        fs::path p = x.path();
        if (fs::is_regular_file(p))
        {
            fileNames.push_back(p.string());
        }
        else if (fs::is_directory(p))
        {
            if (p.filename().string() != "cocostudio" && p.filename().string() != "frameworks")
            {
                vector<string> temp = fileHelper.getDirectoryFile(p.string());
                fileNames.insert(fileNames.end(), temp.begin(), temp.end());
            }
        }
    }
    //过滤文件
    for (auto it = fileNames.begin(); it != fileNames.end(); )
    {
        fs::path p(*it);
        if (p.filename().string().front() == '.')
        {
            it = fileNames.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    //复制到的文件
    vector<string> toFileNames;
    for (int i = 0; i < fileNames.size(); ++i)
    {
        string newFileName = otPath + fileNames[i].substr(mLocationPath.size());
        toFileNames.push_back(getRenameJsFile(newFileName));
    }
    
    cout<<"------------------------"<<endl;
    cout<<"------------------------"<<endl;
    
    for (int i = 0; i < fileNames.size(); ++i)
    {
        fileHelper.copyFile(fileNames[i], toFileNames[i]);
    }
    
    
    vector<string> srcs = {
        "/Users/gongxun/Sites/kwx/src/"
    };
    
    vector<string> ress = {
        "/Users/gongxun/Sites/kwx/res/"
    };
    
    buildConfig(srcs, ress, "/Users/gongxun/Sites/kwx/");
}

void GameGroupHelper::buildConfig(const vector<string> &srcPaths, const vector<string> &recPaths, const string &rootPath)
{
    FileHelper fileHelper;
    {
        //src
        vector<string> fileNames;
        for (int i = 0; i < srcPaths.size(); ++i)
        {
            auto temp = fileHelper.getDirectoryFile(srcPaths[i]);
            fileNames.insert(fileNames.end(), temp.begin(), temp.end());
        }
        for (auto it = fileNames.begin(); it != fileNames.end(); )
        {
            string &filename = *it;
            fs::path p(filename);
            if (p.filename() == "files.js")
            {
                it = fileNames.erase(it);
            }
            else if (p.extension() != ".js")
            {
                it = fileNames.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        fs::ofstream ofile;
        string srcFileName = srcPaths[0] + "files.js";
        ofile.open(srcFileName);
        cout<<"创建文件:"<<srcFileName<<endl;
        
        ofile<<"//Created by MacHelper on "<<getCurDateTime()<<endl;
        ofile<<endl;
        ofile<<"var Files = ["<<endl;
        for (int i = 0; i < fileNames.size(); ++i)
        {
            string file = fileNames[i].substr(rootPath.size());
            ofile<<"    \""<<file<<"\"";
            if (i != fileNames.size() - 1){
                ofile<<","<<endl;
            }
            else
            {
                ofile<<endl;
            }
        }
        ofile<<"];";
        
        ofile.close();
    }
    {
        //rec
        vector<string> fileNames;
        for (int i = 0; i < recPaths.size(); ++i)
        {
            auto temp = fileHelper.getDirectoryFile(recPaths[i]);
            fileNames.insert(fileNames.end(), temp.begin(), temp.end());
        }
        for (auto it = fileNames.begin(); it != fileNames.end(); )
        {
            string &filename = *it;
            fs::path p(filename);
            if (p.extension() == ".DS_Store")
            {
                it = fileNames.erase(it);
            }
            else
            {
                ++it;
            }
        }
        
        fs::ofstream ofile;
        string srcFileName = srcPaths[0] + "resource.js";
        ofile.open(srcFileName);
        cout<<"创建文件:"<<srcFileName<<endl;
        
        ofile<<"//Created by MacHelper on "<<getCurDateTime()<<endl;
        ofile<<endl;
        ofile<<"var Resource = ["<<endl;
        for (int i = 0; i < fileNames.size(); ++i)
        {
            string file = fileNames[i].substr(rootPath.size());
            ofile<<"    \""<<file<<"\"";
            if (i != fileNames.size() - 1){
                ofile<<","<<endl;
            }
            else
            {
                ofile<<endl;
            }
        }
        ofile<<"];";
        
        ofile.close();
    }
}

string GameGroupHelper::getCurDateTime()
{
    auto t = system_clock::to_time_t(system_clock::now());
    auto time = std::put_time(std::localtime(&t), "%Y-%m-%d %X");
    ostringstream oss;
    oss<<time;
    string s = oss.str();
    return s;
}

string GameGroupHelper::getRenameJsFile(const string &jsFile)
{
    string result = jsFile;
    auto p = fs::path(jsFile);
    string fileName = p.filename().string();
    string stem = p.stem().string();
    string extension = p.extension().string();
    
    if (extension != ".js")
    {
        return result;
    }
    else if (fileName == "main.js" || fileName == "sceneHelper.js")
    {
        return result;
    }
    
    string rootPath = p.parent_path().string() + "/";
    
    result = rootPath + stem + mProjectVersion + extension;
    
    return result;
}





















