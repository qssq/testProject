//
//  main.cpp
//  MacHelper
//
//  Created by gongxun on 15/8/4.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include <iostream>
#include "FileHelper.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    FileHelper fh;
    fh.showFileInfo("/Users/gongxun/GitHub/jsTest/MyJSGame/res/favicon.ico");
    
    return 0;
}
