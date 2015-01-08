//
//  COrthoGraphic.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/8.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__COrthoGraphic__
#define __MacOpenGL__COrthoGraphic__

#include "COpenGLBase.h"

class COrthoGraphic : public COpenGLBase
{
public:
    static COrthoGraphic *gOrthoGraphic;
    COrthoGraphic(int argc, char *argv[]);
    ~COrthoGraphic();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultKeyboardFunc(unsigned char key, int x, int y);
    
    GLBatch mTubeBatch;
    GLBatch mInnerBatch;
};

#endif /* defined(__MacOpenGL__COrthoGraphic__) */
