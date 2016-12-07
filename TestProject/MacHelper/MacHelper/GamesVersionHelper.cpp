//
//  GamesVersionHelper.cpp
//  MacHelper
//
//  Created by gongxun on 15/12/8.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#include "GamesVersionHelper.h"
#include "GameVersionServer.h"
#include <iostream>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <algorithm>

namespace fs = boost::filesystem;
string GamesVersionHelper::gLocalPath;
string GamesVersionHelper::gServerPath;

GamesVersionHelper::GamesVersionHelper()
{
    gLocalPath = "/Users/gongxun/oschina/newbeegame/NewbeeHall/";
    gServerPath = "/Users/gongxun/Sites/";
//    mUrl = "http://192.168.2.24/game";
    mUrl = "http://res.16youxi.cc/assets/app_update";
}

GamesVersionHelper::~GamesVersionHelper()
{
    
}

void GamesVersionHelper::setVersion(const string &version)
{
    
}

void GamesVersionHelper::createLocal(const string &hallVersion, const string &lastVersion)
{
    vector<GameVersionLocal> gameLocals;
    {
        GameVersionLocal hall;
        hall.setInfo("Hall", mUrl, hallVersion, "");
        gameLocals.push_back(hall);
        
        GameVersionLocal zjh;
        zjh.setInfo("Zjh", mUrl, lastVersion, hallVersion);
        gameLocals.push_back(zjh);
        
        GameVersionLocal fknn;
        fknn.setInfo("Fknn", mUrl, lastVersion, hallVersion);
        gameLocals.push_back(fknn);
        
        GameVersionLocal brnn;
        brnn.setInfo("Brnn", mUrl, lastVersion, hallVersion);
        gameLocals.push_back(brnn);
        
        GameVersionLocal ddz;
        ddz.setInfo("Ddz", mUrl, lastVersion, hallVersion);
        gameLocals.push_back(ddz);
        
        GameVersionLocal wzq;
        wzq.setInfo("Wzq", mUrl, lastVersion, hallVersion);
        gameLocals.push_back(wzq);
    }
    for (auto it : gameLocals)
    {
        it.createFile();
    }
}

void GamesVersionHelper::createServer(const string &version)
{
    vector<GameVersionServer> gameServers;
    {
        GameVersionServer hall;
        hall.setInfo("Hall", mUrl, version);
        gameServers.push_back(hall);
        
        GameVersionServer zjh;
        zjh.setInfo("Zjh", mUrl, version);
        gameServers.push_back(zjh);
        
        GameVersionServer fknn;
        fknn.setInfo("Fknn", mUrl, version);
        gameServers.push_back(fknn);
        
        GameVersionServer brnn;
        brnn.setInfo("Brnn", mUrl, version);
        gameServers.push_back(brnn);
        
        GameVersionServer ddz;
        ddz.setInfo("Ddz", mUrl, version);
        gameServers.push_back(ddz);
        
        GameVersionServer wzq;
        wzq.setInfo("Wzq", mUrl, version);
        gameServers.push_back(wzq);
    }
    for (auto it : gameServers)
    {
        it.createFile();
    }
}

void GamesVersionHelper::createLocalKwx(const string &version)
{
    gLocalPath = "/Users/gongxun/oschina/gt-card/mobiles/GTKwx/";
    vector<GameVersionLocal> gameLocals;
    {
        GameVersionLocal hall;
        hall.setInfo("Game", "http://192.168.0.100/kwxUpdate", version, "");
        gameLocals.push_back(hall);
    }
    for (auto it : gameLocals)
    {
        it.createFile();
    }
}

void GamesVersionHelper::createServerKwx(const string &version)
{
    vector<GameVersionServer> gameServers;
    {
        GameVersionServer hall;
        hall.setInfo("Game", "http://192.168.0.100/kwxUpdate", version);
        gameServers.push_back(hall);
    }
    for (auto it : gameServers)
    {
        it.createFile();
    }
}

//--------------
//GameVersionLocal
//--------------

GameVersionLocal::GameVersionLocal()
{
    
}

GameVersionLocal::~GameVersionLocal()
{
    
}

void GameVersionLocal::setInfo(const string &name, const string &url, const string &version, const string &version2)
{
    mName = name;
    mUrl = url;
    mVersion = version;
    mOutPath = getHallPath();
    mOutPath2 = "";
    
    mPackageUrl = mUrl + "/game" + mName;
    mRemoteManifestUrl = mPackageUrl + "/project.manifest";
    mRemoteVersionUrl = mPackageUrl + "/version.manifest";
    
    vector<string> keys =
    {
        "#packageUrl",
        "#remoteManifestUrl",
        "#remoteVersionUrl",
        "#version",
        "#groupVersions"
    };
    mKeys = keys;
    
    vector<string> values =
    {
        mPackageUrl,
        mRemoteManifestUrl,
        mRemoteVersionUrl,
        mVersion,
        mVersion
    };
    mValues = values;
    
    vector<string> values2 =
    {
        mPackageUrl,
        mRemoteManifestUrl,
        mRemoteVersionUrl,
        version2,
        version2
    };
    mValues2 = values2;
}

void GameVersionLocal::createFile()
{
    fs::ifstream ifile;
    ifile.open("/Users/gongxun/Sites/machelper/projectLocal.manifest");
    
    vector<fs::ofstream *> ofiles;
    
    fs::ofstream ofile;
    if (mOutPath != "")
    {
        ofile.open(mOutPath);
        ofiles.push_back(&ofile);
        cout<<"创建文件:"<<mOutPath<<endl;
    }
    
    fs::ofstream ofile2;
    if (mOutPath2 != "")
    {
        ofile2.open(mOutPath2);
        ofiles.push_back(&ofile2);
        cout<<"创建文件:"<<mOutPath2<<endl;
    }
    
    string s;
    while (getline(ifile, s))
    {
        for (int i = 0; i < ofiles.size(); ++i)
        {
            if (i == 1)
            {
                (*ofiles[i])<<replaceFile(s, mValues2)<<endl;
            }
            else
            {
                (*ofiles[i])<<replaceFile(s)<<endl;
            }
        }
    }
    
    for (auto *it : ofiles)
    {
        it->close();
    }
    
    ifile.close();
    
}

string GameVersionLocal::replaceFile(const string &s)
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

string GameVersionLocal::replaceFile(const string &s, const vector<string> values)
{
    string result(s);
    
    for (int i = 0; i < mKeys.size(); ++i)
    {
        if (result.find(mKeys[i]) != string::npos)
        {
            result = result.replace(s.find(mKeys[i]), mKeys[i].size(), values[i]);
        }
    }
    
    return result;
}

string GameVersionLocal::getHallPath()
{
    ostringstream oss;
    oss<<GamesVersionHelper::gLocalPath;
    oss<<"res/project";
    oss<<mName;
    oss<<".manifest";
    return oss.str();
}

string GameVersionLocal::getGamePath()
{
    if (mName == "Hall")
    {
        return "";
    }
    
    string upper = mName;
    transform(upper.begin(), upper.end(), upper.begin(), (int (*)(int))tolower);
    ostringstream oss;
    oss<<GamesVersionHelper::gLocalPath;
    oss<<upper;
    oss<<"/";
    oss<<upper;
    oss<<"Res/project";
    oss<<mName;
    oss<<".manifest";
    return oss.str();
}




