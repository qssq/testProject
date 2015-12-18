//
//  ZipDemo.cpp
//  MacHelper
//
//  Created by gongxun on 15/12/11.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#include "ZipDemo.h"
#include <zlib.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

ZipDemo::ZipDemo()
{
    
}

ZipDemo::~ZipDemo()
{
    
}

void ZipDemo::compressFile(const std::string sourceFile, const std::string destFile)
{
    std::ifstream ifile;
    ifile.open(sourceFile, std::ifstream::binary);
    
    ifile.seekg(0, ios::end);
    size_t ifileSize = ifile.tellg();
    ifile.seekg(0, ios::beg);
    char *filePtr = new char[ifileSize];
    ifile.read(filePtr, ifileSize);
    ifile.close();
    
    //开始加密
    uLongf destlen;
    destlen = compressBound(ifileSize);
    Bytef *dest = new Bytef[destlen];
    Bytef *source = (Bytef*)filePtr;
    uLong uLonglen = ifileSize;
    
    int zStatus = compress(dest, &destlen, source, uLonglen);
    if (zStatus == Z_OK)
    {
        //保存到本地
        std::ofstream ofile;
        ofile.open(destFile, std::ofstream::binary);
        char unFileSize[sizeof(uLongf)];
        memcpy(unFileSize, &ifileSize, sizeof(uLongf));
        ofile.write(unFileSize, sizeof(uLongf));
        ofile.write((char *)dest, destlen);
        ofile.close();
        
        cout<<"压缩成功"<<endl;
        cout<<"压缩率为:"<<(float)destlen/(float)uLonglen<<endl;
    }
    else
    {
        cout<<"压缩失败"<<endl;
    }
    delete [] filePtr;
    delete [] dest;
}

void ZipDemo::uncpmpressFile(const std::string sourceFile, const std::string destFile)
{
    std::ifstream ifile;
    ifile.open(sourceFile, std::ifstream::binary);
    
    ifile.seekg(0, ios::end);
    size_t ifileSize = ifile.tellg();
    ifile.seekg(0, ios::beg);
    char *filePtr = new char[ifileSize];
    
    ifile.read(filePtr, ifileSize);
    ifile.close();
    
    //开始解加密
    Bytef *source = (Bytef*)filePtr + sizeof(uLongf);
    uLong uLonglen = ifileSize - sizeof(uLongf);
    
    uLongf destlen = 0;
    memcpy(&destlen, filePtr, sizeof(uLongf));
    Bytef *dest = new Bytef[destlen];
    
    int zStatus = uncompress(dest, &destlen, source, uLonglen);
    if (zStatus == Z_OK)
    {
        //保存到本地
        std::ofstream ofile;
        ofile.open(destFile, std::ofstream::binary);
        ofile.write((char *)dest, destlen);
        ofile.close();
        
        cout<<"解压成功"<<endl;
        cout<<"解压率为:"<<(float)destlen/(float)uLonglen<<endl;
    }
    else
    {
        cout<<"解压失败"<<endl;
    }
    delete [] filePtr;
    delete [] dest;
}











