//
//  GameGroupHelper.hpp
//  MacHelper
//
//  Created by gongxun on 16/11/1.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#ifndef GameGroupHelper_hpp
#define GameGroupHelper_hpp

#include <string>
#include <vector>

using namespace std;

class GameGroupHelper
{
public:
    static GameGroupHelper *singleton();
    
    //生成项目配置文件
    void buildConfigFile();
    
    //生成网页测试项目
    void buildHtmlTest();
    
    //生成kwx配置文件
    void buildConfigKwxFile();
    
    //生成kwx网页测试项目
    void buildHtmlKwxTest();
    
    //生层大富翁配置
    void buildConfigFuweng();
    
    //生成lefan配置
    void buildConfigLefan();
    
    //生成newbee配置
    void buildConfigNewbee();
    
    //生成cc配置
    void buildConfigCC();
    
    //cc配置
    void buildConfigUser(const string &path1, const string &path2);
    
private:
    //项目根目录
    string mProjectPath;
    //项目版本号
    string mProjectVersion;
    
    void buildConfig(const vector<string> &srcPaths, const vector<string> &recPaths, const string &rootPath);
    
    string getCurDateTime();
    
    string getRenameJsFile(const string &jsFile);
    
    static GameGroupHelper *mGameGroupHelper;
    GameGroupHelper();
    ~GameGroupHelper();
};

#endif /* GameGroupHelper_hpp */
