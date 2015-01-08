//
//  CSphereWorld.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/8.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CSphereWorld__
#define __MacOpenGL__CSphereWorld__

#include "COpenGLBase.h"

class CSphereWorld : public COpenGLBase
{
public:
    static CSphereWorld *gSphereWorld;
    CSphereWorld(int argc, char *argv[]);
    ~CSphereWorld();
    virtual void SetupRC();
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultKeyboardFunc(unsigned char key, int x, int y);
    static void defaultSpecialFunc(int key, int x, int y);
    
    GLTriangleBatch		mTorusBatch;
    GLTriangleBatch     mSphereBatch;
    GLBatch				mFloorBatch;
    
    int mStep;
};

#endif /* defined(__MacOpenGL__CSphereWorld__) */
