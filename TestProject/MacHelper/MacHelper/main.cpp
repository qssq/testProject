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
#include "CImgHelper.h"
#include "XMLHelper.h"
#include "SocketServer.h"
#include "CoinFrontTest.h"
#include "GameGroupHelper.h"
#include "GzipHelper.h"
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
    string startPath = argv[0];
    cout<<"程序启动位置:"<<startPath<<endl;
    
    // insert code here...
    cout << "input" <<endl;
    cout << "0:createLocal"<<endl;
    cout << "1:createServer"<<endl;
    cout << "2:zipdemo compress"<<endl;
    cout << "3:zipdemo uncompress"<<endl;
    cout << "4:random list"<<endl;
    cout << "5:CImg test"<<endl;
    cout << "6:xml test"<<endl;
    cout << "7:test"<<endl;
    cout << "8:ipv6 server"<<endl;
    cout << "9:期望"<<endl;
    cout << "10:GameGroup Config"<<endl;
    cout << "11:GameGroup html test"<<endl;
    cout << "12:gzip test"<<endl;
    cout << "13:gtKwx config"<<endl;
    cout << "14:gtKwx html test"<<endl;
    cout << "15:gtKwx create local manifest"<<endl;
    cout << "16:gtKwx create server manifest"<<endl;
    
    string input;
    while (cin>>input)
    {
        if (input == "0")
        {
            GamesVersionHelper gh;
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
            GamesVersionHelper gh;
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
        else if (input == "5")
        {
            CImgHelper cimg;
            cimg.test01();
        }
        else if (input == "6")
        {
            XMLHelper::singleton()->test();
        }
        else if (input == "7")
        {
            ifstream file;
            file.open("snow.plist");
        
            string s;
            while (getline(file, s))
            {
                cout<<s<<endl;
            }
        }
        else if (input == "8")
        {
            SocketServer ss;
            ss.start();
        }
        else if (input == "9")
        {
            CoinFrontTest cft;
            cft.showResult();
        }
        else if (input == "10")
        {
            GameGroupHelper::singleton()->buildConfigFile();
        }
        else if (input == "11")
        {
            GameGroupHelper::singleton()->buildHtmlTest();
        }
        else if (input == "12")
        {
            GzipHelper gh;
            gh.start();
        }
        else if (input == "13")
        {
            GameGroupHelper::singleton()->buildConfigKwxFile();
        }
        else if (input == "14")
        {
            GameGroupHelper::singleton()->buildHtmlKwxTest();
        }
        else if (input == "15")
        {
            GamesVersionHelper gh;
            cout<<"本地文件开始创建"<<endl;
            string version;
            cout<<"输入当前的版本:"<<endl;
            cin>>version;
            gh.createLocalKwx(version);
        }
        else if (input == "16")
        {
            GamesVersionHelper gh;
            cout<<"远程文件开始创建"<<endl;
            string version;
            cout<<"输入当前的版本:"<<endl;
            cin>>version;
            gh.createServerKwx(version);
        }
        else if (input == "17")
        {
            
        }
    }
    
    cout<<"结束"<<endl;
    
    return 0;
}





