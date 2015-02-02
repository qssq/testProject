//
//  CLight.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/26.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CLight__
#define __MacOpenGL__CLight__

#include "COpenGLBase.h"

class CLight : public COpenGLBase
{
public:
    static CLight *gLight;
    CLight(int argc, char *argv[]);
    ~CLight();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    
private:
    GLBatch	triangleBatch;
    GLTriangleBatch torusBatch;
    
    GLuint	diffuseLightShader;	// The diffuse light shader
    GLint	locAmbient;			// The location of the ambient color
    GLint   locDiffuse;			// The location of the diffuse color
    GLint   locSpecular;		// The location of the specular color
    GLint	locLight;			// The location of the Light in eye coordinates
    GLint	locMVP;				// The location of the ModelViewProjection matrix uniform
    GLint	locMV;				// The location of the ModelView matrix uniform
    GLint	locNM;				// The location of the Normal matrix uniform
    GLint   locTexture;
    GLuint  texture;
};

#endif /* defined(__MacOpenGL__CLight__) */
