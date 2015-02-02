//
//  CCellShading.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/27.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CCellShading__
#define __MacOpenGL__CCellShading__

#include "COpenGLBase.h"

class CCellShading : public COpenGLBase
{
public:
    static CCellShading *gCellShading;
    CCellShading(int argc, char *argv[]);
    ~CCellShading();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    
private:
    GLTriangleBatch     torusBatch;
    
    GLuint	toonShader;	        // The dissolving light shader
    GLint	locLight;			// The location of the Light in eye coordinates
    GLint	locMVP;				// The location of the ModelViewProjection matrix uniform
    GLint	locMV;				// The location of the ModelView matrix uniform
    GLint	locNM;				// The location of the Normal matrix uniform
    GLint   locColorTable;		// The location of the color table
    
    GLuint	texture;
};

#endif /* defined(__MacOpenGL__CCellShading__) */
