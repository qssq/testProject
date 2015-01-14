//
//  CPyramid.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/12.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CPyramid__
#define __MacOpenGL__CPyramid__

#include "COpenGLBase.h"

class CPyramid : public COpenGLBase
{
public:
    static CPyramid *gPyramid;
    CPyramid(int argc, char *argv[]);
    ~CPyramid();
    virtual void SetupRC();
    virtual void ShutdownRC();
    static void defaultDisplayFunc();
    
    void MakePyramid(GLBatch& pyramidBatch);
    GLuint  mTextureID;
    GLBatch mPyramidBatch;
};

#endif /* defined(__MacOpenGL__CPyramid__) */
