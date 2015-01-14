//
//  CSphereWorld.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/8.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CSphereWorld.h"
#include <StopWatch.h>

CSphereWorld *CSphereWorld::gSphereWorld = NULL;

CSphereWorld::CSphereWorld(int argc, char *argv[]) : COpenGLBase(argc, argv), mStep(0)
{
    gSphereWorld = this;
    setDisplayFunc(CSphereWorld::defaultDisplayFunc);
    setReshapeFunc(CSphereWorld::defaultReshapeFunc);
    setKeyboardFunc(CSphereWorld::defaultKeyboardFunc);
    setSpecialFunc(CSphereWorld::defaultSpecialFunc);
}

CSphereWorld::~CSphereWorld()
{
    gSphereWorld = NULL;
}

void CSphereWorld::SetupRC()
{
    shaderManager.InitializeStockShaders();
    
    glEnable(GL_DEPTH_TEST);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glClearColor(0, 0, 0, 1);
    
    //torus
    gltMakeTorus(gSphereWorld->mTorusBatch, 0.4, 0.15, 30, 30);
    
    // This make a sphere
    gltMakeSphere(gSphereWorld->mSphereBatch, 0.1f, 26, 13);
    
    //floor
    GLBatch &floorBatch =  gSphereWorld->mFloorBatch;
    floorBatch.Begin(GL_LINES, 324);
    for(GLfloat x = -20.0; x <= 20.0f; x+= 0.5)
    {
        floorBatch.Vertex3f(x, -0.55f, 20.0f);
        floorBatch.Vertex3f(x, -0.55f, -20.0f);
        
        floorBatch.Vertex3f(20.0f, -0.55f, x);
        floorBatch.Vertex3f(-20.0f, -0.55f, x);
    }
    floorBatch.End();
    
    //spheres
    for (int i = 0; i < spheresCout; ++i)
    {
        GLfloat x = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        GLfloat z = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        mSpheres[i].SetOrigin(x, 0.0f, z);
    }
}

void CSphereWorld::defaultDisplayFunc()
{
    // Color values
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
    static GLfloat vTorusColor[] = { 1.0f, 0.8f, 0.8f, 1.0f };
    static GLfloat vSphereColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    
    static CStopWatch	rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //保存单位矩阵
    modelViewMatrix.PushMatrix();
    
    //摄像机
    M3DMatrix44f camera;
    gSphereWorld->mCameraFrame.GetCameraMatrix(camera);
    modelViewMatrix.PushMatrix(camera);
    
    //光源
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    m3dTransformVector4(vLightEyePos, vLightPos, camera);
    
    //地板
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
    gSphereWorld->mFloorBatch.Draw();
    
    //小球
    for(int i = 0; i < spheresCout; ++i)
    {
        modelViewMatrix.PushMatrix();
        modelViewMatrix.MultMatrix(gSphereWorld->mSpheres[i]);
        shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vSphereColor);
        gSphereWorld->mSphereBatch.Draw();
        modelViewMatrix.PopMatrix();
    }
    
    modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
    
    //保存平移
    modelViewMatrix.PushMatrix();
    
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightEyePos, vTorusColor);
    
    gSphereWorld->mTorusBatch.Draw();
    
    //消除旋转
    modelViewMatrix.PopMatrix();
    
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightEyePos, vSphereColor);
    
    gSphereWorld->mSphereBatch.Draw();
    
    //消除平移
    modelViewMatrix.PopMatrix();
    //消除摄像机
    modelViewMatrix.PopMatrix();

    // Do the buffer Swap
    glutSwapBuffers();
    
    // Tell GLUT to do it again
    glutPostRedisplay();
}

void CSphereWorld::defaultReshapeFunc(int width, int height)
{
    glViewport(0, 0, width, height);
    viewFrustum.SetPerspective(35, (float)width/(float)height, 1, 100);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void CSphereWorld::defaultKeyboardFunc(unsigned char key, int x, int y)
{
    if(key == 32)
    {
        gSphereWorld->mStep++;
        
        if(gSphereWorld->mStep > 1)
            gSphereWorld->mStep = 0;
    }
    
    switch(gSphereWorld->mStep)
    {
        case 0:
            glutSetWindowTitle("lines");
            break;
        case 1:
            glutSetWindowTitle("p");
            break;
    }
    
    glutPostRedisplay();

}

void CSphereWorld::defaultSpecialFunc(int key, int x, int y)
{
    float linear = 0.2f;
    float angular = float(m3dDegToRad(10.0f));
    if(key == GLUT_KEY_UP)
        gSphereWorld->mCameraFrame.MoveForward(linear);
    
    if(key == GLUT_KEY_DOWN)
        gSphereWorld->mCameraFrame.MoveForward(-linear);
    
    if(key == GLUT_KEY_LEFT)
        gSphereWorld->mCameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        gSphereWorld->mCameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}














