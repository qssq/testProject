//
//  COpenGLFunc.h
//  MacOpenGL
//
//  Created by gongxun on 14/12/11.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__COpenGLFunc__
#define __MacOpenGL__COpenGLFunc__

#include <GLTools.h>	// OpenGL toolkit
#include <GLMatrixStack.h>
#include <GLFrame.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLGeometryTransform.h>

#include <math.h>
#ifdef __APPLE__
#include <glut/glut.h>
#else
#define FREEGLUT_STATIC
#include <GL/glut.h>
#endif

typedef void (*FP_DISPLAY)(void);
typedef void (*FP_RESHAPE)(int width, int height);
typedef void (*FP_KEYBOARD)(unsigned char key, int x, int y);
typedef void (*FP_SPECIA)(int key, int x, int y);

class COpenGLFunc
{
public:
    ~COpenGLFunc();
    //OpenGL
    static GLFrustum           viewFrustum;         // View Frustum 视景体
    static GLMatrixStack       modelViewMatrix;      // Modelview Matrix
    static GLMatrixStack       projectionMatrix;    // Projection Matrix
    static GLShaderManager     shaderManager;       // Shader Manager
    static GLGeometryTransform transformPipeline;   // Geometry Transform Pipeline  集合变换管线
    
    static M3DMatrix44f        shadowMatrix;
    static GLFrame             viewFrame;
    static GLFrame             CameraFrame;
    
    //func
    void setDefaultFunc();
    void setFunc();
    
    void setDisplayFunc(void (*func)(void));
    void setReshapeFunc(void (*func)(int width, int height));
    void setKeyboardFunc(void (*func)(unsigned char key, int x, int y));
    void setSpecialFunc(void (*func)(int key, int x, int y));
    
    FP_DISPLAY mFP_DISPLAY;
    FP_RESHAPE mFP_RESHAPE;
    FP_KEYBOARD mFP_KEYBOARD;
    FP_SPECIA mFP_SPECIA;
    
    static void defaultDisplayFunc();
    static void defaultReshapeFunc(int width, int height);
    static void defaultKeyboardFunc(unsigned char key, int x, int y);
    static void defaultSpecialFunc(int key, int x, int y);
};

#endif /* defined(__MacOpenGL__COpenGLFunc__) */
