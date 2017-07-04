//
//  ChangeFileName.hpp
//  MacHelper
//
//  Created by gongxun on 17/6/5.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef ChangeFileName_hpp
#define ChangeFileName_hpp

#include <string>
#include "FileHelper.h"

using namespace std;

class ChangeFileName
{
public:
    ChangeFileName();
    ~ChangeFileName();
    
    void start(const string &path);
    
private:
    FileHelper mFileHelper;
};

#endif /* ChangeFileName_hpp */
