//
//  GameVersionServer.cpp
//  MacHelper
//
//  Created by gongxun on 15/12/11.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#include "GameVersionServer.h"
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <algorithm>

#include "GamesVersionHelper.h"
#include "GXMD5.h"

namespace fs = boost::filesystem;

GameVersionServer::GameVersionServer()
{
    
}

GameVersionServer::~GameVersionServer()
{
    
}

void GameVersionServer::setInfo(const string &name, const string &url, const string &version)
{
    mName = name;
    mUrl = url;
    mVersion = version;
    mOutPath = getProjectPath();
    mOutPath2 = getVersionPath();
    
    mPackageUrl = mUrl + "/game" + mName;
    mRemoteManifestUrl = mPackageUrl + "/project.manifest";
    mRemoteVersionUrl = mPackageUrl + "/version.manifest";
    setUpdateValue();
    
    vector<string> keys =
    {
        "#packageUrl",
        "#remoteManifestUrl",
        "#remoteVersionUrl",
        "#version",
        "#groupVersions",
        "#update1path",
        "#update2path",
        "#update1md5",
        "#update2md5"
    };
    mKeys = keys;
    
    vector<string> values =
    {
        mPackageUrl,
        mRemoteManifestUrl,
        mRemoteVersionUrl,
        mVersion,
        mVersion,
        mUpdate1path,
        mUpdate2path,
        mUpdate1md5,
        mUpdate2md5
    };
    mValues = values;
}

void GameVersionServer::createFile()
{
    //project
    {
        fs::ifstream ifile;
        ifile.open("/Users/gongxun/Sites/machelper/project.manifest");
        
        fs::ofstream ofile;
        ofile.open(mOutPath);
        cout<<"创建文件:"<<mOutPath<<endl;
        
        string s;
        while (getline(ifile, s))
        {
            ofile<<replaceFile(s)<<endl;
        }
        
        ofile.close();
        ifile.close();
        
    }
    
    //version
    {
        fs::ifstream ifile;
        ifile.open("/Users/gongxun/Sites/machelper/version.manifest");
        
        fs::ofstream ofile;
        ofile.open(mOutPath2);
        cout<<"创建文件:"<<mOutPath2<<endl;
        
        string s;
        while (getline(ifile, s))
        {
            ofile<<replaceFile(s)<<endl;
        }
        
        ofile.close();
        ifile.close();
        
    }
}

string GameVersionServer::replaceFile(const string &s)
{
    string result(s);
    
    for (int i = 0; i < mKeys.size(); ++i)
    {
        if (result.find(mKeys[i]) != string::npos)
        {
            result = result.replace(s.find(mKeys[i]), mKeys[i].size(), mValues[i]);
        }
    }
    
    return result;
}

string GameVersionServer::getProjectPath()
{
    ostringstream oss;
    oss<<GamesVersionHelper::gServerPath;
    oss<<"kwxUpdate/";
    oss<<"game";
    oss<<mName;
    oss<<"/project.manifest";
    return oss.str();
}

string GameVersionServer::getVersionPath()
{
    ostringstream oss;
    oss<<GamesVersionHelper::gServerPath;
    oss<<"kwxUpdate/";
    oss<<"game";
    oss<<mName;
    oss<<"/version.manifest";
    return oss.str();
}

void GameVersionServer::setUpdateValue()
{
    string upper = mName;
    transform(upper.begin(), upper.end(), upper.begin(), (int (*)(int))tolower);
    
    mUpdate1path = "src.zip";
    mUpdate2path = "res.zip";
    
    string zipSrc = getMD5Path() + "/src.zip";
    string zipRes = getMD5Path() + "/res.zip";
    
    mUpdate1md5 = md5file(zipSrc);
    mUpdate2md5 = md5file(zipRes);
}
string GameVersionServer::getMD5Path()
{
    ostringstream oss;
    oss<<GamesVersionHelper::gServerPath;
    oss<<"kwxUpdate/";
    oss<<"game";
    oss<<mName;
    return oss.str();
}














