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

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "input 0:createLocal  1:createServer"<<endl;
    
    GamesVersionHelper gh;
    string input;
    while (cin>>input)
    {
        if (input == "0")
        {
            cout<<"本地文件开始创建"<<endl;
            gh.createLocal();
        }
        else if (input == "1")
        {
            cout<<"远程文件开始创建"<<endl;
            gh.createServer();
        }
    }
    
    cout<<"结束"<<endl;
    
    return 0;
}
