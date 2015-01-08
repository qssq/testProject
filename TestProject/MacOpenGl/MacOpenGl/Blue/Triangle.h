//
//  Triangle.h
//  MacOpenGL
//
//  Created by gongxun on 14/11/10.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__Triangle__
#define __MacOpenGL__Triangle__

#include "COpenGLBase.h"

class Triangle : public COpenGLBase
{
public:
    Triangle(int argc, char* argv[]);
    ~Triangle();
    virtual void SetupRC();
    static void defaultDisplayFunc();
};

#endif /* defined(__MacOpenGL__Triangle__) */
