//
//  CShadedTriangle.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/21.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CShadedTriangle__
#define __MacOpenGL__CShadedTriangle__

#include "COpenGLBase.h"

class CShadedTriangle : public COpenGLBase
{
public:
    static CShadedTriangle *gShadedTriangle;
    CShadedTriangle(int argc, char *argv[]);
    ~CShadedTriangle();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    
private:
    GLBatch	triangleBatch;
    GLint	myIdentityShader;
};

#endif /* defined(__MacOpenGL__CShadedTriangle__) */
