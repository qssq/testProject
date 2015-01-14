//
//  CObjects.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/6.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CObjects.h"

GLTriangleBatch CObjects::sphereBatch;
GLTriangleBatch CObjects::torusBatch;
GLTriangleBatch CObjects::cylinderBatch;
GLTriangleBatch CObjects::coneBatch;
GLTriangleBatch CObjects::diskBatch;

int CObjects::mStep = 0;

CObjects::CObjects(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    setDisplayFunc(CObjects::defaultDisplayFunc);
    setKeyboardFunc(CObjects::defaultKeyboardFunc);
    setReshapeFunc(CObjects::defaultReshapeFunc);
}

CObjects::~CObjects()
{
    
}

void CObjects::SetupRC()
{
    // Black background
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f );
    
    shaderManager.InitializeStockShaders();
    
    glEnable(GL_DEPTH_TEST);
    
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
//    viewFrame.MoveForward(-20.0f);
    
    mStep = 4;
    
    // Sphere
    gltMakeSphere(sphereBatch, 3.0, 10, 20);
    
    // Torus
    gltMakeTorus(torusBatch, 3.0f, 0.75f, 15, 15);
    
    //cylinder
    gltMakeCylinder(cylinderBatch, 3, 3, 4, 10, 2);
    
    //cone
    gltMakeCylinder(coneBatch, 3, 0, 4, 10, 2);
    
    //disk
    gltMakeDisk(diskBatch, 3, 5, 10, 2);
}

void CObjects::defaultDisplayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    
    switch(mStep)
    {
        case 0:
            DrawWireFramedBatch(&sphereBatch);
            break;
        case 1:
            DrawWireFramedBatch(&torusBatch);
            break;
        case 2:
            DrawWireFramedBatch(&cylinderBatch);
            break;
        case 3:
            DrawWireFramedBatch(&coneBatch);
            break;
        case 4:
            DrawWireFramedBatch(&diskBatch);
            break;
    }
    
    modelViewMatrix.PopMatrix();
    
    // Flush drawing commands
    glutSwapBuffers();
}

void CObjects::defaultReshapeFunc(int width, int height)
{
    // Prevent a divide by zero
    if(height == 0)
        height = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);
    
    float ortho = 10;
    viewFrustum.SetOrthographic(-ortho, ortho, -ortho, ortho, -20, 20);
    //    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
}

void CObjects::defaultKeyboardFunc(unsigned char key, int x, int y)
{
    if(key == 32)
    {
        mStep++;
        
        if(mStep > 4)
            mStep = 0;
    }
    
    switch(mStep)
    {
        case 0:
            glutSetWindowTitle("Sphere");
            break;
        case 1:
            glutSetWindowTitle("Torus");
            break;
        case 2:
            glutSetWindowTitle("Cylinder");
            break;
        case 3:
            glutSetWindowTitle("Cone");
            break;
        case 4:
            glutSetWindowTitle("Disk");
            break;
    }
    
    glutPostRedisplay();
}