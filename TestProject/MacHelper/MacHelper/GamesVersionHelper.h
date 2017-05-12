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
    
    void createLocal(const string &hallVersion, const string &lastVersion);
    void createServer(const string &version);
    
    void setVersion(const string &version);
    
    void createLocalKwx(const string &version);
    void createServerKwx(const string &version);
    
    void createLocalHall(const string &version);
    void createServerHall(const string &version);
    
    void createLocalLefan(const string &version);
    void createServerLefan(const string &version);
    
    void createServerNewbee(const string &version);
private:
    string mUrl;
};

class GameVersionLocal
{
public:
    GameVersionLocal();
    ~GameVersionLocal();
    
    //version1 hallRes/ version2 name/
    void setInfo(const string &name, const string &url, const string &version, const string &version2);
    
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
    vector<string> mValues2;
    
    string replaceFile(const string &s);
    string replaceFile(const string &s, const vector<string> values);
    string getHallPath();
    string getGamePath();
};

#endif /* GamesVersionHelper_hpp */
