//
//  CModelviewProjection.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/8.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CModelviewProjection__
#define __MacOpenGL__CModelviewProjection__

#include "COpenGLBase.h"

class CModelviewProjection : public COpenGLBase
{
public:
    static CModelviewProjection *gModelviewProjection;
    CModelviewProjection(int argc, char *argv[]);
    ~CModelviewProjection();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    
    GLTriangleBatch mTorusBatch;
    GLBatch mInnerBatch;
};

#endif /* defined(__MacOpenGL__CModelviewProjection__) */
