//
//  CTunnel.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/14.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CTunnel__
#define __MacOpenGL__CTunnel__

#include "COpenGLBase.h"

class CTunnel : public COpenGLBase
{
public:
    static CTunnel *gTunnel;
    CTunnel(int argc, char *argv[]);
    ~CTunnel();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultSpecialFunc(int key, int x, int y);
    static void ProcessMenu(int value);
    
    enum textureCount
    {
        TEXTURE_BRICK = 0,
        TEXTURE_FLOOR = 1,
        TEXTURE_CEILING = 2,
        TEXTURE_COUNT = 3
    };
    
    GLuint mTextures[TEXTURE_COUNT];
    string mTextureFiles[TEXTURE_COUNT];
    
    GLBatch             floorBatch;
    GLBatch             ceilingBatch;
    GLBatch             leftWallBatch;
    GLBatch             rightWallBatch;
    
    GLfloat             mViewZ;
    GLfloat             mViewRotate;
};

#endif /* defined(__MacOpenGL__CTunnel__) */
