//
//  GameProtoFileHelper.cpp
//  MacHelper
//
//  Created by gongxun on 17/11/2.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "GameProtoFileHelper.h"
#include "FileHelper.h"
#include <fstream>
#include "Defines.h"

GameProtoFileHelper::GameProtoFileHelper()
: mBaseProtoName("gt_base.proto")
{
    
}

GameProtoFileHelper::~GameProtoFileHelper()
{
    
}

void GameProtoFileHelper::start(const string &protoDir, const string &projectDir)
{
    FileHelper fileHelper;
    vector<string> protoFiles = fileHelper.getDirectoryFile(protoDir);
    sort(protoFiles.begin(), protoFiles.end());
    
    //过滤文件
    for (auto it = protoFiles.begin(); it != protoFiles.end(); )
    {
        string item = *it;
        if (item.substr(protoDir.length(), 2) == "/."){
            it = protoFiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
    
    //创建temp文件
    ofstream ofile;
    ofile.open("temp.txt", ios::binary | ios::trunc);
    ofile<<"//Created by MacHelper on "<<getCurDateTime()<<endl;
    
    //string流
    ostringstream oss;
    
    sort(protoFiles.begin(), protoFiles.end(), [=](string a, string b){
        if (a.substr(a.length() - mBaseProtoName.length(), mBaseProtoName.length()) == "gt_base.proto")
        {
            return false;
        }
        
        if (b.substr(b.length() - mBaseProtoName.length(), mBaseProtoName.length()) == "gt_base.proto")
        {
            return false;
        }
        
        return false;
    });
    
    for (int i = 0; i < protoFiles.size(); i++)
    {
        const string fileName = protoFiles[i];
        mIsCommentedOuting = false;
        
        string littleName = fileName.substr(protoDir.length() + 1, fileName.length() - protoDir.length() - 1);
        ofile<<"//fileName: "<<littleName<<endl;
        
        ifstream ifile;
        ifile.open(fileName, ios::binary);
        string temp;
        while (!ifile.eof()) {
            getline(ifile, temp, '\n');
            
            string outStr;
            if (getFilterStr(temp, fileName, outStr))
            {
                ofile<<outStr<<endl;
                oss<<outStr<<endl;
            }
        }
        ifile.close();
        
        ofile<<endl;
        ofile<<endl;
        
        cout<<"添加文件:"<<fileName<<" 完成"<<endl;
    }
    
    ofile.close();
    cout<<"合并protobuf文件 完成"<<endl;
    
    //转换base64
    string oustring = oss.str();
    string base64_str;
    fileHelper.Base64Encode(oustring, base64_str);
    
    ofstream ofileBase64;
    ofileBase64.open("temp.js", ios::binary | ios::trunc);
    ofileBase64<<"//Created by MacHelper on "<<getCurDateTime()<<endl;
    ofileBase64<<"var protobufFile64 = \"";
    ofileBase64<<base64_str;
    ofileBase64<<"\";"<<endl;
    ofileBase64.close();
    cout<<"本地protobuf base js文件 完成"<<endl;
    
    movoFile(projectDir);
}

bool GameProtoFileHelper::getFilterStr(const string &str, const string &fileName, string &outStr)
{
    outStr = str;
    string fileSSS = fileName.substr(fileName.length() - mBaseProtoName.length(), mBaseProtoName.length());
    bool isBaseProto = fileName.substr(fileName.length() - mBaseProtoName.length(), mBaseProtoName.length()) == "gt_base.proto";
    
    //注释代码注释
    if (str.length() >= 2)
    {
        bool isReturn = false;
        if (str.find("/*") != string::npos)
        {
            mIsCommentedOuting = true;
            isReturn = true;
        }
        
        if (str.find("*/") != string::npos)
        {
            mIsCommentedOuting = false;
            isReturn = true;
        }
        
        if (isReturn)
        {
            return false;
        }
    }
    
    if (mIsCommentedOuting)
    {
        return false;
    }
    
    //过滤掉其他文件中头
    vector<string> filters;
    filters.push_back("package gt_msg;");
    filters.push_back("import");
    if (!isBaseProto)
    {
        for (int i = 0; i < filters.size(); i++)
        {
            string filter = filters[i];
            if (str.length() >= filter.length() && str.find(filter) != string::npos)
            {
                return false;
            }
        }
    }
    
    //移除掉注释
    string commentedOutKey = "//";
    auto findCommentedOutIndex = str.find(commentedOutKey);
    if (findCommentedOutIndex != string::npos)
    {
        outStr = str.substr(0, findCommentedOutIndex);
    }
    
    //移除掉空的行
    if (outStr.length() == 0)
    {
        return false;
    }
    
    return true;
}

void GameProtoFileHelper::movoFile(const string &projectDir)
{
    cout<<"开始移动文件 dir:"<<projectDir<<endl;
    
    FileHelper fileHelper;
    fileHelper.copyFile("temp.txt", projectDir + "/tools/baseProto.txt");
    fileHelper.copyFile("temp.js", projectDir + "/src/net/gameMsgProtobufDefines.js");
    
    
    cout<<"移动移动文件结束"<<endl;
}











