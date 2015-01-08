//
//  Primitives.h
//  MacOpenGL
//
//  Created by gongxun on 14/11/19.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__Primitives__
#define __MacOpenGL__Primitives__

#include "COpenGLBase.h"

class CPrimitives : public COpenGLBase
{
public:
    CPrimitives(int argc, char* argv[]);
    ~CPrimitives();
    virtual void SetupRC();
    static GLBatch triangleBatch;
    static GLBatch pointBatch;
    static void defaultDisplayFunc();
    static void DrawWireFramedBatch(GLBatch* pBatch);
};

#endif /* defined(__MacOpenGL__Primitives__) */
