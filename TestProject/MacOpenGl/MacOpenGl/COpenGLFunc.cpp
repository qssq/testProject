//
//  COpenGLFunc.cpp
//  MacOpenGL
//
//  Created by gongxun on 14/12/11.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#include "COpenGLFunc.h"

GLFrame             COpenGLFunc::viewFrame;
GLFrame             COpenGLFunc::CameraFrame;
GLFrustum           COpenGLFunc::viewFrustum;
GLMatrixStack       COpenGLFunc::modelViewMatrix;
GLMatrixStack       COpenGLFunc::projectionMatrix;
GLShaderManager     COpenGLFunc::shaderManager;

GLGeometryTransform COpenGLFunc::transformPipeline;
M3DMatrix44f        COpenGLFunc::shadowMatrix;

COpenGLFunc::~COpenGLFunc()
{
    
}

void COpenGLFunc::setDefaultFunc()
{
    mFP_DISPLAY = defaultDisplayFunc;
    mFP_RESHAPE = defaultReshapeFunc;
    mFP_KEYBOARD = defaultKeyboardFunc;
    mFP_SPECIA = defaultSpecialFunc;
}

void COpenGLFunc::setFunc()
{
    glutDisplayFunc(mFP_DISPLAY);
    glutReshapeFunc(mFP_RESHAPE);
    glutKeyboardFunc(mFP_KEYBOARD);
    glutSpecialFunc(mFP_SPECIA);
}

void COpenGLFunc::setDisplayFunc(void (*func)(void))
{
    mFP_DISPLAY = func;
}

void COpenGLFunc::setReshapeFunc(void (*func)(int width, int height))
{
    mFP_RESHAPE = func;
}

void COpenGLFunc::setKeyboardFunc(void (*func)(unsigned char key, int x, int y))
{
    mFP_KEYBOARD = func;
}

void COpenGLFunc::setSpecialFunc(void (*func)(int key, int x, int y))
{
    mFP_SPECIA = func;
}

void COpenGLFunc::defaultDisplayFunc()
{
    
}

void COpenGLFunc::defaultReshapeFunc(int width, int height)
{
    // Prevent a divide by zero
    if(height == 0)
        height = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);
    
    //创建投影矩阵 并将他压入投影矩阵堆栈中
    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 100.0f);        //角度 深度(min-max)
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    //设置变换管线以使用两个矩阵堆栈
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void COpenGLFunc::defaultKeyboardFunc(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void COpenGLFunc::defaultSpecialFunc(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_DOWN)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 1.0f, 0.0f, 0.0f);
    
    if(key == GLUT_KEY_LEFT)
        viewFrame.RotateWorld(m3dDegToRad(-5.0), 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        viewFrame.RotateWorld(m3dDegToRad(5.0), 0.0f, 1.0f, 0.0f);
    
    // Refresh the Window
    glutPostRedisplay();
}