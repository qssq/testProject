//
//  CObjects.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/6.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CObjects__
#define __MacOpenGL__CObjects__

#include "COpenGLBase.h"

class CObjects : public COpenGLBase
{
public:
    CObjects(int argc, char *argv[]);
    ~CObjects();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultKeyboardFunc(unsigned char key, int x, int y);
    static void defaultReshapeFunc(int width, int height);
    
    static GLTriangleBatch     sphereBatch;
    static GLTriangleBatch     torusBatch;
    static GLTriangleBatch     cylinderBatch;
    static GLTriangleBatch     coneBatch;
    static GLTriangleBatch     diskBatch;

    static int mStep;
};

#endif /* defined(__MacOpenGL__CObjects__) */
