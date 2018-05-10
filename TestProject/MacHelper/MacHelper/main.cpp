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
#include "CImageHandle.h"
#include "UpdateManager.h"
#include "Defines.h"
#include "FileHelper.h"
#include "ChangeFileName.h"
#include "ImageKeLeHelper.h"
#include "GameProtoFileHelper.h"
#include "GameRealeaseProject.h"

using namespace std;

//int add(int a, int b)
//{
//    return a + b;
//}

//TEST(demoTest, demoTestInput)
//{
//    EXPECT_EQ(2, add(1, 2));
//}


void handEvent(const string &input, const string &input2, const string &input3)
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
        file.open("gt_user_info.txt");
        
        string s;
        while (getline(file, s))
        {
            cout<<"\""<<s<<"\","<<endl;
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
        GamesVersionHelper gh;
        cout<<"本地文件开始创建"<<endl;
        string version;
        cout<<"输入当前的版本:"<<endl;
        cin>>version;
        gh.createLocalHall(version);
    }
    else if (input == "18")
    {
        GamesVersionHelper gh;
        cout<<"远程文件开始创建"<<endl;
        string version;
        cout<<"输入当前的版本:"<<endl;
        cin>>version;
        gh.createServerHall(version);
    }else if (input == "19")
    {
        
        fs::path p("protobuffer.txt");
        
        fs::ifstream ifile;
        ifile.open(p);
        
        fs::ofstream ofile;
        ofile.open("protobuffer2.txt");
        
        string s;
        while (getline(ifile, s))
        {
            string va = s;
            auto fi = va.find("//", 0);
            if (fi != va.npos){
                va = va.substr(0, fi);
            }
            
            ofile<<va<<endl;
        }
    }
    else if (input == "20")
    {
        GameGroupHelper::singleton()->buildConfigFuweng();
    }
    else if (input == "21")
    {
        CImageHandle imageHandle;
        imageHandle.handlerKw();
    }
    else if (input == "22")
    {
        GameGroupHelper::singleton()->buildConfigLefan();
    }
    else if (input == "23")
    {
        GamesVersionHelper gh;
        cout<<"本地文件开始创建"<<endl;
        string version;
        cout<<"输入当前的版本:"<<endl;
        cin>>version;
        gh.createLocalLefan(version);
    }
    else if (input == "24")
    {
        GamesVersionHelper gh;
        cout<<"远程文件开始创建"<<endl;
        string version;
        cout<<"输入当前的版本:"<<endl;
        cin>>version;
        gh.createServerLefan(version);
    }
    else if (input == "25")
    {
        GameGroupHelper::singleton()->buildConfigNewbee();
    }
    else if (input == "26")
    {
        GamesVersionHelper gh;
        cout<<"远程文件开始创建"<<endl;
        string version;
        cout<<"输入当前的版本:"<<endl;
        cin>>version;
        gh.createServerNewbee(version);
    }
    else if (input == "27")
    {
        ChangeFileName cfn;
        cfn.start("/Users/gongxun/Desktop/test/9/");
    }
    else if (input == "28")
    {
        ImageKeLeHelper ikh;
        ikh.start();
    }
    else if (input == "100")
    {
        cout<<"开始构造增量更新包 测试版"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/kwx/", "http://qxkwx.oss-cn-beijing.aliyuncs.com/testGame");
        //            UpdateManager::singleton()->start("/Users/gongxun/Sites/update/kwx/", "http://192.168.1.200/update/kwx");
    }
    else if (input == "101")
    {
        cout<<"开始构造增量更新包"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/newbee/", "http://192.168.1.106/update/newbee");
    }
    else if (input == "102")
    {
        cout<<"开始构造增量更新包 正式版"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/kwxreal/", "http://qxkwx.oss-cn-beijing.aliyuncs.com/gameGame");
    }
    else if (input == "103")
    {
        cout<<"开始构造增量更新包 备份测试"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/cdnAli/", "http://192.168.1.200/update/cdnAli");
        
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/cndQiNiu/", "http://192.168.1.200/update/cndQiNiu");
    }
    else if (input == "104")
    {
        GameProtoFileHelper gpfh;
        gpfh.start("/Users/gongxun/oschina/kwxclient/proto", "/Users/gongxun/oschina/kwxclient/mobiles/GTKwx");
    }
    else if (input == "105")
    {
//        GameGroupHelper::singleton()->buildConfigCC();
        GameGroupHelper::singleton()->buildConfigUser(input2, input3);
    }
    else if (input == "106")
    {
        GameProtoFileHelper gpfh;
        gpfh.start(input2, input3);
//        gpfh.start("/Users/gongxun/bitbucket/gtdemo/GTServer/proto", "/Users/gongxun/oschina/ccClient/mobiles/CCFire");
    }
    else if (input == "107")
    {
        GameRealeaseProject grp;
//        grp.start("/Users/gongxun/oschina/ccClient/mobiles/CCFire");
        grp.start(input2);
    }
    else if (input == "108")
    {
        cout<<"开始构造增量更新包 CC正式版"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/cc/", "http://ccgame.oss-cn-beijing.aliyuncs.com/ccgame", "1.0.8");
    }
    else if (input == "109")
    {
        cout<<"开始构造增量更新包 CC测试版"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/cctest/", "http://ccgame.oss-cn-beijing.aliyuncs.com/cctest");
    }
    else if (input == "110")
    {
        GameGroupHelper::singleton()->buildConfigUser("/Users/gongxun/oschina/gtkwx/mobiles/GTKwx", "");
    }
    else if (input == "111")
    {
        GameGroupHelper::singleton()->buildConfigUser("/Users/gongxun/oschina/game_prototype/mobiles/game", "");
    }
    else if (input == "112")
    {
        GameProtoFileHelper gpfh;
        gpfh.start("/Users/gongxun/oschina/game_prototype/proto", "/Users/gongxun/oschina/game_prototype/mobiles/game");
    }
    else if (input == "113")
    {
        cout<<"开始构造增量更新包 测试版"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/prototype/", "https://h7game.oss-cn-beijing.aliyuncs.com/testGame");
    }
    else if (input == "114")
    {
        cout<<"开始构造增量更新包 正式版本"<<endl;
        UpdateManager::singleton()->start("/Users/gongxun/Sites/update/prototypeReal/", "https://h7game.oss-cn-beijing.aliyuncs.com/gameGame");
    }
    else if (input == "115")
    {
        GameRealeaseProject grp;
        grp.start("/Users/gongxun/oschina/game_prototype/mobiles/game");
        
        GameGroupHelper::singleton()->buildConfigUser("/Users/gongxun/oschina/game_prototype/mobiles/game", "/Users/gongxun/oschina/game_prototype/mobiles/game/publish");
    }
    else if (input == "116")
    {
        GameGroupHelper::singleton()->buildConfigUser("/Users/gongxun/oschina/kwxclient/mobiles/GTKwx/robot", "");
       
        GameProtoFileHelper gpfh;
        gpfh.start("/Users/gongxun/oschina/kwxclient/mobiles/GTKwx/robot/proto", "/Users/gongxun/oschina/kwxclient/mobiles/GTKwx/robot");
    }
    else if (input == "117")
    {
        GameGroupHelper::singleton()->buildConfigUser("/Users/gongxun/oschina/kkGame/mobiles/newKwx", "");
    }
    else if (input == "118")
    {
        GameProtoFileHelper gpfh;
        gpfh.start("/Users/gongxun/oschina/kwxclient/proto", "/Users/gongxun/oschina/kkGame/mobiles/newKwx");
    }
}

int main(int argc, const char * argv[]) {
    
//    testing::InitGoogleTest(&argc, const_cast<char **>(argv));
//    return RUN_ALL_TESTS();
    string startPath = argv[0];
    string projectName = FileHelper::gProjectName;
    FileHelper::gStartPath = startPath.substr(0, startPath.size() - projectName.size());
    cout<<"程序启动位置:"<<startPath<<endl;
    
    string arg1 = "";
    string arg2 = "";
    string arg3 = "";
    if (argc > 1)
    {
        arg1 = argv[1];
    }
    if (argc > 2)
    {
        arg2 = argv[2];
    }
    if (argc > 3)
    {
        arg3 = argv[3];
    }
    
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
    cout << "17:GameGroup create local manifest"<<endl;
    cout << "18:GameGroup create server manifest"<<endl;
    cout << "19:删除注释"<<endl;
    cout << "20:fuweng Config"<<endl;
    cout << "21:切分图片"<<endl;
    cout << "22:lefan config"<<endl;
    cout << "23:lefan local manifest"<<endl;
    cout << "24:lefan setver manifest"<<endl;
    cout << "25:newbee config"<<endl;
    cout << "26:newbee setver manifest"<<endl;
    cout << "27:change file name"<<endl;
    cout << "28:KeLe file"<<endl;
    cout << "100:kwx增量更新"<<endl;
    cout << "101:newbee增量更新"<<endl;
    cout << "102:kwx增量更新(真实版本)"<<endl;
    cout << "103:备用cdn测试"<<endl;
    cout << "104:合并proto kwx"<<endl;
    cout << "105:cc config"<<endl;
    cout << "106:cc 合并protobuf"<<endl;
    cout << "107:cc 生成正式项目代码"<<endl;
    cout << "108:cc 编译正式版本"<<endl;
    cout << "109:cc 编译测试版本"<<endl;
    cout << "110: gtKwx files"<<endl;
    cout << "111: prototype files"<<endl;
    cout << "112: prototype proto"<<endl;
    cout << "113: prototype增量更新 测试版"<<endl;
    cout << "114: prototype增量更新 正式版本"<<endl;
    cout << "115: prototype 生成正式项目版本"<<endl;
    cout << "116: robot"<<endl;
    cout << "117: kk config"<<endl;
    cout << "118: kk proto"<<endl;
    
    if (arg1 != "")
    {
        handEvent(arg1, arg2, arg3);
    }
    else
    {
        string input;
        while (cin>>input)
        {
            handEvent(input, "", "");
        }
    }
    
    cout<<"结束"<<endl;
    
    return 0;
}






