//
//  CSmoother.h
//  MacOpenGL
//
//  Created by gongxun on 14/12/18.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CSmoother__
#define __MacOpenGL__CSmoother__

#include "COpenGLBase.h"

class CSmoother : public COpenGLBase
{
public:
    CSmoother(int argc, char *argv[]);
    ~CSmoother();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void ProcessMenu(int value);
    
    static GLBatch smallStarBatch;
    static GLBatch mediumStarBatch;
    static GLBatch largeStarBatch;
    static GLBatch mountainRangeBatch;
    static GLBatch moonBatch;
};

#endif /* defined(__MacOpenGL__CSmoother__) */
