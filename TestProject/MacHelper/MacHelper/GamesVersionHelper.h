//
//  GamesVersionHelper.hpp
//  MacHelper
//
//  Created by gongxun on 15/12/8.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#ifndef GamesVersionHelper_h
#define GamesVersionHelper_h

#include <string>
#include <vector>

using namespace std;

class GamesVersionHelper
{
public:
    static string gLocalPath;
    static string gServerPath;
public:
    GamesVersionHelper();
    ~GamesVersionHelper();
    
    void createLocal();
    void createServer();
    
    void setVersion(const string &version);
private:
    string mUrl;
};

class GameVersionLocal
{
public:
    GameVersionLocal();
    ~GameVersionLocal();
    
    void setInfo(const string &name, const string &url, const string &version);
    
    void createFile();
private:
    string mName;
    string mUrl;
    string mVersion;
    string mOutPath;
    string mOutPath2;
    
    string mPackageUrl;
    string mRemoteManifestUrl;
    string mRemoteVersionUrl;
    
    vector<string> mKeys;
    vector<string> mValues;
    
    string replaceFile(const string &s);
    string getHallPath();
    string getGamePath();
};

#endif /* GamesVersionHelper_hpp */
