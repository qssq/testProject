//
//  TestPrimrestart.h
//  MacOpenGL
//
//  Created by gongxun on 14/11/4.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__TestPrimrestart__
#define __MacOpenGL__TestPrimrestart__

#include "stdio.h"
#include "COpenGLBase.h"

class TestPrimrestart : public COpenGLBase
{
public:
    TestPrimrestart(int argc, char* argv[]);
    ~TestPrimrestart();
    static void display();
    static void reshape(int width, int height);
};

#endif /* defined(__MacOpenGL__TestPrimrestart__) */
