//
//  GameVersionServer.hpp
//  MacHelper
//
//  Created by gongxun on 15/12/11.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#ifndef GameVersionServer_h
#define GameVersionServer_h

#include <string>
#include <vector>

using namespace std;

class GameVersionServer
{
public:
    GameVersionServer();
    ~GameVersionServer();
    
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
    string mUpdate1path;
    string mUpdate2path;
    string mUpdate1md5;
    string mUpdate2md5;
    
    vector<string> mKeys;
    vector<string> mValues;
    void setUpdateValue();
    
    string replaceFile(const string &s);
    string getProjectPath();
    string getVersionPath();
    string getMD5Path();
};

#endif /* GameVersionServer_hpp */
