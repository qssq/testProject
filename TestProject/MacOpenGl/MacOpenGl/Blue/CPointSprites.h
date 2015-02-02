//
//  CPointSprites.h
//  MacOpenGL
//
//  Created by gongxun on 15/2/2.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CPointSprites__
#define __MacOpenGL__CPointSprites__

#include "COpenGLBase.h"

class CPointSprites : public COpenGLBase
{
public:
    static CPointSprites *gPointSprites;
    CPointSprites(int argc, char *argv[]);
    ~CPointSprites();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    
    enum attribute
    {
        NUM_STARS = 1000
    };
private:
    GLBatch             starsBatch;
    
    GLuint	starFieldShader;	// The point sprite shader
    GLint	locMVP;				// The location of the ModelViewProjection matrix uniform
    GLint   locTimeStamp;       // The location of the time stamp
    GLint	locTexture;			// The location of the  texture uniform
    
    GLuint	starTexture;		// The star texture texture object
};

#endif /* defined(__MacOpenGL__CPointSprites__) */
