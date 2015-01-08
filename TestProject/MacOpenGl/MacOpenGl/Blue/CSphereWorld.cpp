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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
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
}

void CSphereWorld::defaultDisplayFunc()
{
    // Color values
    static GLfloat vFloorColor[] = { 0.0f, 1.0f, 0.0f, 1.0f};
    static GLfloat vTorusColor[] = { 1.0f, 0.8f, 0.8f, 1.0f };
    static GLfloat vSphereColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    
    static CStopWatch	rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //保存单位矩阵
    modelViewMatix.PushMatrix();
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
    gSphereWorld->mFloorBatch.Draw();
    
    modelViewMatix.Translate(0.0f, 0.0f, -2.5f);
    
    //保存平移
    modelViewMatix.PushMatrix();
    
    modelViewMatix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(),
                                 vTorusColor);
    
    gSphereWorld->mTorusBatch.Draw();
    
    //消除旋转
    modelViewMatix.PopMatrix();
    
    modelViewMatix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatix.Translate(0.8f, 0.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(),
                                 vSphereColor);
    
    gSphereWorld->mSphereBatch.Draw();
    
    //消除平移
    modelViewMatix.PopMatrix();

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
    transformPipeline.SetMatrixStacks(modelViewMatix, projectionMatrix);
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
    
}