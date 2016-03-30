//
//  main.cpp
//  MacHelper
//
//  Created by gongxun on 15/8/4.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include <iostream>
#include "FileHelper.h"
#include "GamesVersionHelper.h"
#include "ZipDemo.h"
#include "GXMD5.h"
#include "RandomList.h"
//#include <gtest/gtest.h>

using namespace std;

//int add(int a, int b)
//{
//    return a + b;
//}

//TEST(demoTest, demoTestInput)
//{
//    EXPECT_EQ(2, add(1, 2));
//}

int main(int argc, const char * argv[]) {
    
//    testing::InitGoogleTest(&argc, const_cast<char **>(argv));
//    return RUN_ALL_TESTS();
    
    // insert code here...
    cout << "input" <<endl;
    cout << "0:createLocal"<<endl;
    cout << "1:createServer"<<endl;
    cout << "2:zipdemo compress"<<endl;
    cout << "3:zipdemo uncompress"<<endl;
    cout << "4:random list"<<endl;
    
    GamesVersionHelper gh;
    string input;
    while (cin>>input)
    {
        if (input == "0")
        {
            cout<<"本地文件开始创建"<<endl;
            string hallVersion, lastVersion;
            cout<<"输入当前的版本:"<<endl;
            cin>>hallVersion;
            cout<<"输入的上次的版本:"<<endl;
            cin>>lastVersion;
            gh.createLocal(hallVersion, lastVersion);
        }
        else if (input == "1")
        {
            cout<<"远程文件开始创建"<<endl;
            string version;
            cout<<"输入当前的版本:"<<endl;
            cin>>version;
            gh.createServer(version);
        }
        else if (input == "2")
        {
            string file;
            cout<<"输入压缩文件名:"<<endl;
            cin>>file;
            ZipDemo zd;
            zd.compressFile("zipdemo/" + file, "zipdemo/temp.gzip");
        }
        else if (input == "3")
        {
            string file;
            cout<<"输入解压后文件名:"<<endl;
            cin>>file;
            ZipDemo zd;
            zd.uncpmpressFile("zipdemo/temp.gzip", "zipdemo/" + file);
        }
        else if (input == "4")
        {
            RandomList rl;
            rl.start();
        }
    }
    
    cout<<"结束"<<endl;
    
    return 0;
}
