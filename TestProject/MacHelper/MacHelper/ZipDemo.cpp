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
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

ZipDemo::ZipDemo()
{
    
}

ZipDemo::~ZipDemo()
{
    
}

void ZipDemo::test()
{
//    char text[] = "test01gongxuntest02";
//    const Bytef *testptr = (Bytef *)text;
//    uLong tlen = strlen(text) + 1;  /* 需要把字符串的结束符'\0'也一并处理 */
//    char* buf = nullptr;
//    Bytef *bufptr = nullptr;
//    uLongf blen;
//    
//    /* 计算缓冲区大小，并为其分配内存 */
//    blen = compressBound(tlen); /* 压缩后的长度是不会超过blen的 */
//    if((buf = (char*)malloc(sizeof(char) * blen)) == NULL)
//    {
//        printf("no enough memory!\n");
//        return;
//    }
//    bufptr = (Bytef*)buf;
//    
//    /* 压缩 */
//    if(compress(bufptr, &blen, testptr, tlen) != Z_OK)
//    {
//        printf("compress failed!\n");
//        return;
//    }
//    int MAX_LEN = 1024 * 100;
//    
//    FILE* fp1 = fopen("test.txt","rb");
//    unsigned char* pBufferRes=new unsigned char[MAX_LEN];
//    unsigned char* pBufferDes=new unsigned char[MAX_LEN];
//    
//    memset(pBufferRes, 0, MAX_LEN);
//    memset(pBufferDes,0,MAX_LEN);
//    fread(pBufferRes, sizeof(unsigned char), MAX_LEN - 1, fp1);
//    uLongf lSize = strlen((const char*)pBufferRes);
//    uLongf desLen;
//    desLen = compressBound(lSize);
//    
//    int nError= compress(pBufferDes, &desLen, pBufferRes, lSize);
//    if (nError == Z_OK)
//    {
//        //保存到本地
//        FILE* fp2 = NULL;
//        fp2=fopen("demo.zip","wb");
//        //将压缩后的信息写入文件
//        fwrite(&lSize, sizeof(uLong), 1, fp2);    /* 写入源文件长度 */
//        fwrite(&desLen, sizeof(uLong), 1, fp2);    /* 写入目标数据长度 */
//        fwrite(pBufferDes, sizeof(unsigned char), desLen, fp2);
//        fclose(fp2);
//        
//        cout<<"压缩成功"<<endl;
//    }
//    else
//    {
//        cout<<"压缩失败"<<endl;
//    }
//    fclose(fp1);
    //获取需要加密的文件
    std::ifstream ifile;
    ifile.open("test.txt", std::ifstream::binary);
    
    ifile.seekg(0, ios::end);
    size_t ifileSize = ifile.tellg();
    char filePtr[ifileSize];
    
    ifile.seekg(0, ios::beg);
    ifile.read(filePtr, ifileSize);
    ifile.close();
    
    //开始加密
    uLongf destlen;
    destlen = compressBound(ifileSize);
    Bytef *dest = (Bytef*)malloc(sizeof(char) * destlen);
    Bytef *source = (Bytef*)filePtr;
    uLong uLonglen = ifileSize;

    int zStatus = compress(dest, &destlen, source, uLonglen);
    if (zStatus == Z_OK)
    {
        //保存到本地
        std::ofstream ofile;
        ofile.open("demo.zip", std::ofstream::binary);
        ofile.write((char *)dest, destlen);
        ofile.close();
        
        cout<<"压缩成功"<<endl;
    }
    else
    {
        cout<<"压缩失败"<<endl;
    }
}












