//
//  updateManager.hpp
//  MacHelper
//
//  Created by gongxun on 17/5/10.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef updateManager_hpp
#define updateManager_hpp

#include <string>
#include <vector>
#include <map>
#include "FileHelper.h"

class UpdateManager
{
public:
    static UpdateManager *singleton();
    
    //path:工作目录 strPackageUrl:更新http位置
    void start(const string &path, const string &strPackageUrl);
private:
    FileHelper mFileHelper;
    string mStrPackageUrl;
    string mCurrentVersion;
    string mOnlyMarkeStr;
    
    //排序文件夹 按照3点版本号排序
    vector<string> sortVersionDirectory(const vector<string> &directory);
    
    //返回两个目录的不同文件
    vector<string> getDifferenceFiles(const string &newPath, const string &oldPath);
    
    //压缩文件操作
    bool setCompressionFile(const string &workPath, const vector<string> &files, const string &filePath, const string &zipName);
    
    //生成配置文件
    bool createConifgFile(const vector<string> &addZip, const string &allZip, const string workPath, const string &currentVersion);
    
    //返回文件名
    string getFileNameByParentPath(const string &fileName, const string &path);
    
    //更具最新的版本号返回唯一标示
    string getOnlyMarkedForVersion(const string &versionStr);
    
    static UpdateManager *mUpdateManager;
    UpdateManager();
    ~UpdateManager();
};

#endif /* updateManager_hpp */
