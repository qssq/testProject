//
//  COpenGlBase.h
//  MacOpenGl
//
//  Created by gongxun on 14/10/31.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGl__COpenGlBase__
#define __MacOpenGl__COpenGlBase__

#include "COpenGLFunc.h"
#include <iostream>

using namespace std;

class COpenGLBase : public COpenGLFunc
{
public:
    COpenGLBase(int argc, char* argv[]);
    ~COpenGLBase();
    void mainLoop();
    virtual void SetupRC();
    
    static void logMatrix44(const M3DMatrix44f &m);
    static void DrawWireFramedBatch(GLTriangleBatch* pBatch);
};


#endif /* defined(__MacOpenGl__COpenGlBase__) */
