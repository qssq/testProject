//
//  CShadedTriangle.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/21.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CShadedTriangle.h"
#include <StopWatch.h>

CShadedTriangle *CShadedTriangle::gShadedTriangle = NULL;

CShadedTriangle::CShadedTriangle(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gShadedTriangle = this;
    setDisplayFunc(CShadedTriangle::defaultDisplayFunc);
}

CShadedTriangle::~CShadedTriangle()
{
    gShadedTriangle = NULL;
}

void CShadedTriangle::SetupRC()
{
    cout<<glGetString(GL_RENDERER)<<endl;
    cout<<glGetString(GL_VERSION)<<endl;
    
    // Blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    viewFrame.MoveForward(4.0f);
    
    // Make the torus
    gltMakeTorus(torusBatch, .80f, 0.25f, 52, 26);
    
    myIdentityShader = gltLoadShaderPairWithAttributes("/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/FlatShader.vp", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/FlatShader.fp", 1, GLT_ATTRIBUTE_VERTEX, "vVertex");
    
    locMVP = glGetUniformLocation(myIdentityShader, "mvpMatrix");
    locColor = glGetUniformLocation(myIdentityShader, "vColorValue");
    
    cout<<myIdentityShader<<endl;
}

void CShadedTriangle::ShutdownRC()
{
    glDeleteProgram(myIdentityShader);
}

void CShadedTriangle::defaultDisplayFunc()
{
    static CStopWatch rotTimer;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 30.0f, 0.0f, 1.0f, 0.0f);
    
    GLfloat vColor[] = { 0.1f, 0.1f, 1.f, 1.0f };
    
    glUseProgram(gShadedTriangle->myIdentityShader);
    glUniform4fv(gShadedTriangle->locColor, 1, vColor);
    glUniformMatrix4fv(gShadedTriangle->locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    gShadedTriangle->torusBatch.Draw();
    
    modelViewMatrix.PopMatrix();
    
    
    glutSwapBuffers();
    glutPostRedisplay();
}

















