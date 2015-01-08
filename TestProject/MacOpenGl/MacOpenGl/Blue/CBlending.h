//
//  CBlending.h
//  MacOpenGL
//
//  Created by gongxun on 14/12/17.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CBlending__
#define __MacOpenGL__CBlending__

#include "COpenGLBase.h"

class CBlending : public COpenGLBase
{
public:
    CBlending(int argc, char* argv[]);
    ~CBlending();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultSpecialFunc(int key, int x, int y);
    
    static GLBatch	squareBatch;
    static GLBatch greenBatch;
    static GLBatch redBatch;
    static GLBatch blueBatch;
    static GLBatch blackBatch;
    
    static GLfloat vVerts[];
};

#endif /* defined(__MacOpenGL__CBlending__) */
