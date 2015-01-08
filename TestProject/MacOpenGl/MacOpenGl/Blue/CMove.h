//
//  CMove.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/6.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CMove__
#define __MacOpenGL__CMove__

#include "COpenGLBase.h"

class CMove : public COpenGLBase
{
public:
    CMove(int argc, char *argv[]);
    ~CMove();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultSpecialFunc(int key, int x, int y);

    static GLBatch	squareBatch;
    static GLfloat xPos;
    static GLfloat yPos;
    static GLfloat blockSize;
};

#endif /* defined(__MacOpenGL__CMove__) */
