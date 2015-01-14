//
//  CPyramid.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/12.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CPyramid.h"

CPyramid *CPyramid::gPyramid = NULL;

CPyramid::CPyramid(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gPyramid = this;
    setDisplayFunc(CPyramid::defaultDisplayFunc);
}

CPyramid::~CPyramid()
{
    gPyramid = NULL;
}

void CPyramid::MakePyramid(GLBatch& pyramidBatch)
{
    pyramidBatch.Begin(GL_TRIANGLES, 18, 1);
    
    M3DVector3f vFrontLeft = { -1.0f, -1.0f, 1.0f };
    M3DVector3f vFrontRight = { 1.0f, -1.0f, 1.0f };
    M3DVector3f vBackLeft = { -2.0f, -1.0f, -1.0f };
    M3DVector3f vBackRight = { 2.0f, -1.0f, -1.0f };
    
    // Bottom of pyramid
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackLeft);
    
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackRight);
    
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
    pyramidBatch.Vertex3fv(vFrontRight);
    
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
    pyramidBatch.Vertex3fv(vFrontLeft);
    
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackLeft);
    
    pyramidBatch.Normal3f(0.0f, -1.0f, 0.0f);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
    pyramidBatch.Vertex3fv(vFrontRight);
    
    
    M3DVector3f vApex = { 0.0f, 1.0f, 0.0f };
    M3DVector3f n;
    
    // Front of Pyramid
    m3dFindNormal(n, vApex, vFrontLeft, vFrontRight);
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
    pyramidBatch.Vertex3fv(vApex);		// Apex
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vFrontLeft);		// Front left corner
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
    pyramidBatch.Vertex3fv(vFrontRight);		// Front right corner
    
    
    m3dFindNormal(n, vApex, vBackLeft, vFrontLeft);
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
    pyramidBatch.Vertex3fv(vApex);		// Apex
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackLeft);		// Back left corner
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vFrontLeft);		// Front left corner
    
    m3dFindNormal(n, vApex, vFrontRight, vBackRight);
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
    pyramidBatch.Vertex3fv(vApex);				// Apex
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
    pyramidBatch.Vertex3fv(vFrontRight);		// Front right corner
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackRight);			// Back right cornder
    
    
    m3dFindNormal(n, vApex, vBackRight, vBackLeft);
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.5f, 1.0f);
    pyramidBatch.Vertex3fv(vApex);		// Apex
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackRight);		// Back right cornder
    
    pyramidBatch.Normal3fv(n);
    pyramidBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
    pyramidBatch.Vertex3fv(vBackLeft);		// Back left corner
    
    pyramidBatch.End();
}

void CPyramid::SetupRC()
{
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
    
    shaderManager.InitializeStockShaders();
    
    glEnable(GL_DEPTH_TEST);
    
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
    bool a = LoadTGATexture(getFileName("stone2.tga").c_str(), GL_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    if (a)
    {
        cout<<"加载图片 成功"<<endl;
    }
    else
    {
        cout<<"加载图片 失败"<<endl;
    }
    
    MakePyramid(mPyramidBatch);
    
    CameraFrame.MoveForward(-7.0f);
}

void CPyramid::ShutdownRC()
{
    glDeleteTextures(1, &mTextureID);
}

void CPyramid::defaultDisplayFunc()
{
    static GLfloat vLightPos [] = { 10.0f, 0.0f, 0.0f };
    static GLfloat vWhite [] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix();
    M3DMatrix44f mCamera;
    CameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.MultMatrix(mCamera);
    
    M3DMatrix44f mObjectFrame;
    viewFrame.GetMatrix(mObjectFrame);
    modelViewMatrix.MultMatrix(mObjectFrame);
    
//    glBindTexture(GL_TEXTURE_2D, gPyramid->mTextureID);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightPos, vWhite, 0);
    
    gPyramid->mPyramidBatch.Draw();
    
    
    modelViewMatrix.PopMatrix();
    
    // Flush drawing commands
    glutSwapBuffers();
}









