//
//  CModelviewProjection.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/8.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CModelviewProjection.h"
#include <StopWatch.h>

CModelviewProjection *CModelviewProjection::gModelviewProjection = NULL;

CModelviewProjection::CModelviewProjection(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gModelviewProjection = this;
    setDisplayFunc(CModelviewProjection::defaultDisplayFunc);
    setReshapeFunc(CModelviewProjection::defaultReshapeFunc);
}

CModelviewProjection::~CModelviewProjection()
{
    gModelviewProjection = NULL;
}

void CModelviewProjection::SetupRC()
{
    // Black background
    glClearColor(0.8f, 0.8f, 0.8f, 1.0f );
    
    glEnable(GL_DEPTH_TEST);
    
    shaderManager.InitializeStockShaders();
    
    // This makes a torus
    gltMakeTorus(gModelviewProjection->mTorusBatch, 0.4f, 0.15f, 30, 30);
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void CModelviewProjection::defaultDisplayFunc()
{
    // Set up time based animation
    static CStopWatch rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    cout<<"秒数:"<<yRot<<endl;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Matrix Variables
    M3DMatrix44f mTranslate, mRotate, mModelview, mModelViewProjection;
    
    // Create a translation matrix to move the torus back and into sight
    m3dTranslationMatrix44(mTranslate, 0.0f, 0.0f, -2.5f);
    
    // Create a rotation matrix based on the current value of yRot
    m3dRotationMatrix44(mRotate, m3dDegToRad(yRot), 0.0f, 1.0f, 0.0f);
    
    // Add the rotation to the translation, store the result in mModelView
    m3dMatrixMultiply44(mModelview, mTranslate, mRotate);
    
    // Add the modelview matrix to the projection matrix,
    // the final matrix is the ModelViewProjection matrix.
    m3dMatrixMultiply44(mModelViewProjection, viewFrustum.GetProjectionMatrix(),mModelview);
    
    // Pass this completed matrix to the shader, and render the torus
    GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mModelViewProjection, vBlack);
    gModelviewProjection->mTorusBatch.Draw();
    
    
    // Swap buffers, and immediately refresh
    glutSwapBuffers();
    glutPostRedisplay();
}

void CModelviewProjection::defaultReshapeFunc(int width, int height)
{
    // Prevent a divide by zero
    if(height == 0)
        height = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);
    
    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
}