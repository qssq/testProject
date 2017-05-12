//
//  updateManager.cpp
//  MacHelper
//
//  Created by gongxun on 17/5/10.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "UpdateManager.h"
#include "Defines.h"
#include "GXMD5.h"

UpdateManager *UpdateManager::mUpdateManager = nullptr;

UpdateManager *UpdateManager::singleton()
{
    if (!mUpdateManager)
    {
        mUpdateManager = new UpdateManager();
    }
    return mUpdateManager;
}

UpdateManager::UpdateManager()
{
    
}

UpdateManager::~UpdateManager()
{
    
}

void UpdateManager::start()
{
    ///1.找到所有文件夹
    ///2.所有文件夹和最新的文件夹对比 记录下对应filename
    ///3.开始移动改动文件到主目录打包 然后移动包到工作目录 打包完之后删除
    ///4.移动最新文件到主目录打包 然后移动包到工作目录 打包完之后删除
    ///5.写更新配置
    
    //工作目录
    string path = "/Users/gongxun/Sites/update/kwx/";
    //增量包
    vector<string> mUpdateZipFiles;
    //全包
    string mAllUpdateZipFile;
    
    ///1
    //找到所有文件夹 然后所有
    cout<<"1 开始寻找更新文件夹..."<<endl;
    vector<string> directorys = mFileHelper.getDirectory(path);
    directorys = sortVersionDirectory(directorys);
    cout<<"找到更新文件夹"<<endl;
    for (const auto &item : directorys)
    {
        cout<<"更新文件夹:"<<item<<endl;
    }
    cout<<endl;
    
    //最新文件夹
    string newDirectory = directorys.back();
    
    ///2
    //找到所有文件的对比
    cout<<"2 开始进行对比文件夹 最新版本文件夹是:"<<newDirectory<<"..."<<endl;
    map<string, vector<string>> differenceMaps;
    for (const auto &directory : directorys)
    {
        differenceMaps[directory] = getDifferenceFiles(newDirectory, directory);
        cout<<"版本:"<<directory<<" 找到改动:"<<differenceMaps[directory].size()<<endl;
    }
    cout<<endl;
    
    ///3
    //压缩文件
    cout<<"3 开始压缩增量文件夹..."<<endl;
    for (auto item : differenceMaps)
    {
        //拿出需要移动的文件
        string itemPath = item.first;
        vector<string> differenceFiles = item.second;
        
        //没有变化就不管他
        if (differenceFiles.size() == 0)
        {
            continue;
        }
        
        string toVersion = itemPath.substr(itemPath.rfind("/") + 1, itemPath.size() - itemPath.rfind("/") + 1);
        string zipFileName = "update_" + toVersion + ".zip";
        
        setCompressionFile(path, differenceFiles, newDirectory, zipFileName);
        mUpdateZipFiles.push_back(path + zipFileName);
        cout<<"增量更新文件:"<<path + zipFileName<<"生成完毕"<<endl;
    }
    cout<<endl;
    
    ///4
    //压缩全更新文件
    cout<<"4 开始压缩全更新文件夹..."<<endl;
    {
        vector<string> files = mFileHelper.getDirectoryFile(newDirectory);
        string zipFileName = "update_all.zip";
        setCompressionFile(path, files, newDirectory, zipFileName);
        mAllUpdateZipFile = path + zipFileName;
        cout<<"全量更新文件:"<<mAllUpdateZipFile<<"生成完毕"<<endl;
    }
    cout<<endl;
    
    ///5
    //生成配置文件
    cout<<"5 开始生成配置文件..."<<endl;
    string currentVersion = newDirectory.substr(newDirectory.rfind("/") + 1, newDirectory.size() - newDirectory.rfind("/") + 1);
    createConifgFile(mUpdateZipFiles, mAllUpdateZipFile, path, currentVersion);
    cout<<endl;
    
    cout<<"end 增量包生成成功"<<endl;
}

vector<string> UpdateManager::sortVersionDirectory(const vector<string> &directory)
{
    vector<string> result(directory.begin(), directory.end());
    
    auto getStringMax = [](string a, string b){
        int aNum = getIntForString(a);
        int bNum = getIntForString(b);
        
        return aNum - bNum;
    };
    
    sort(result.begin(), result.end(), [=](string &a, string &b){
        string aName = mFileHelper.getFileName(a);
        string bName = mFileHelper.getFileName(b);
        
        vector<string> aArr = split(aName, '.');
        vector<string> bArr = split(bName, '.');
        
        if (aArr.size() != 3 || bArr.size() != 3)
        {
            return false;
        }
        
        for (int i = 0; i < 3; ++i)
        {
            int temp  = getStringMax(aArr[i], bArr[i]);
            if (temp != 0)
            {
                return temp < 0;
            }
        }
        
        return false;
    });
    
    return result;
}

vector<string> UpdateManager::getDifferenceFiles(const string &newPath, const string &oldPath)
{
    vector<string> result;
    
    vector<string> newFiles = mFileHelper.getDirectoryFile(newPath);
    vector<string> oldFiles = mFileHelper.getDirectoryFile(oldPath);
    
    for (int i = 0; i < newFiles.size(); ++i)
    {
        string newFile = newFiles[i];
        string oldFile = oldPath + newFile.substr(newPath.size(), newFile.size() - newPath.size());
        
        //如果没找到就插入
        if (find(oldFiles.begin(), oldFiles.end(), oldFile) == oldFiles.end())
        {
            result.push_back(newFile);
            continue;
        }
        
        //如果md5值不一致就插入
        string md51 = md5file(newFile);
        string md52 = md5file(oldFile);
        if (md51 != md52)
        {
            result.push_back(newFile);
            continue;
        }
    }
    
    
    return result;
}

bool UpdateManager::setCompressionFile(const string &workPath, const vector<string> &files, const string &filePath, const string &zipName)
{
    //拿出需要移动的文件
    string itemPath = workPath;
    vector<string> differenceFiles(files.begin(), files.end());
    
    //移动文件到指定目录
    string toPath = FileHelper::gStartPath;
    string fromPath = filePath;
    
    for (const auto file : differenceFiles)
    {
        string toFileName = toPath + file.substr(filePath.size(), file.size() - filePath.size());
        mFileHelper.copyFile(file, toFileName);
    }
    
    //移动完之后压缩
    string zipFileName = zipName;
    
    char zipchar1[300];
    sprintf(zipchar1, "zip -q -r -g '%s%s' 'res'", toPath.c_str(), zipFileName.c_str());
    int status = system(zipchar1);
    
    char zipchar2[300];
    sprintf(zipchar2, "zip -q -r -g '%s%s' 'src'", toPath.c_str(), zipFileName.c_str());
    status = system(zipchar2);
    
    //压缩之后移动到工作目录
    mFileHelper.copyFile(toPath + zipFileName, workPath + zipFileName);
    
    //删除程序目录的文件
    mFileHelper.removeFile(toPath + "res");
    mFileHelper.removeFile(toPath + "src");
    mFileHelper.removeFile(toPath + zipFileName);
    
    return true;
}

bool UpdateManager::createConifgFile(const vector<string> &addZip, const string &allZip, const string workPath, const string &currentVersion)
{
    string strProject = "project.manifest";
    string strVersion = "version.manifest";
    string strPackageUrl = "http://192.168.1.106/update/kwx";
    
    
    //生成project文件
    fs::ofstream ofile;
    string proFileName = workPath + strProject;
    ofile.open(proFileName);
    {
        ofile<<"{"<<endl;
        ofile<<"    \"packageUrl\" : \""<<strPackageUrl<<"\","<<endl;
        ofile<<"    \"remoteManifestUrl\" : \""<<strPackageUrl + "/" + strProject<<"\","<<endl;
        ofile<<"    \"remoteVersionUrl\" : \""<<strPackageUrl + "/" + strVersion<<"\","<<endl;
        ofile<<"    \"version\" : \""<<currentVersion<<"\","<<endl;
        ofile<<"    \"groupVersions\" : {"<<endl;
        ofile<<"        \"1\" : \""<<currentVersion<<"\""<<endl;
        ofile<<"    },"<<endl;
        ofile<<"    \"engineVersion\" : \"3.13.1\","<<endl;
        ofile<<"    \"assets\" : {"<<endl;
        ofile<<"        \"update1\" : {"<<endl;
        ofile<<"            \"path\" : \""<<getFileNameByParentPath(allZip, workPath)<<"\","<<endl;
        ofile<<"            \"md5\" : \""<<md5file(allZip)<<"\","<<endl;
        ofile<<"            \"compressed\" : true,"<<endl;
        ofile<<"            \"group\" : 1"<<endl;
        ofile<<"        }"<<endl;
        ofile<<"    },"<<endl;
        ofile<<"    \"searchPaths\" : [],"<<endl;
        
        //增量更新
        ofile<<"    \"downAssets\" : ["<<endl;
        int len = 0;
        for (const auto &file : addZip)
        {
            ++len;
            string fileName = getFileNameByParentPath(file, workPath);
            string version = fileName.substr(fileName.find("_") + 1);
            version = version.substr(0, version.rfind("."));
            char temp[200];
            sprintf(temp, "        {\"version\" : \"%s\", \"path\" : \"%s\"}", version.c_str(), fileName.c_str());
            
            string outString = temp;
            if (len != addZip.size())
            {
                outString += ",";
            }
            ofile<<outString<<endl;
        }
        ofile<<"    ],"<<endl;
        
        //全包更新
        ofile<<"    \"allDownAsset\" : ["<<endl;
        ofile<<"        \""<<getFileNameByParentPath(allZip, workPath)<<"\""<<endl;
        ofile<<"    ]"<<endl;
        ofile<<"}"<<endl;
    }
    ofile.close();
    
    //生成version文件
    fs::ofstream ofile2;
    string verFileName = workPath + strVersion;
    ofile2.open(verFileName);
    {
        ofile2<<"{"<<endl;
        ofile2<<"    \"packageUrl\" : \""<<strPackageUrl<<"\","<<endl;
        ofile2<<"    \"remoteManifestUrl\" : \""<<strPackageUrl + "/" + strProject<<"\","<<endl;
        ofile2<<"    \"remoteVersionUrl\" : \""<<strPackageUrl + "/" + strVersion<<"\","<<endl;
        ofile2<<"    \"version\" : \""<<currentVersion<<"\","<<endl;
        ofile2<<"    \"groupVersions\" : {"<<endl;
        ofile2<<"        \"1\" : \""<<currentVersion<<"\""<<endl;
        ofile2<<"    },"<<endl;
        ofile2<<"    \"engineVersion\" : \"3.13.1\","<<endl;
        ofile2<<"    \"updateInfo\" : \"发现新版本，是否升级客户端?\","<<endl;
        ofile2<<"    \"updateSize\" : \"20M\""<<endl;
        ofile2<<"}"<<endl;
    }
    ofile2.close();
    
    return true;
}

string UpdateManager::getFileNameByParentPath(const string &fileName, const string &path)
{
    return fileName.substr(path.size(), fileName.size() - path.size());
}
















