//
//  CShadedTriangle.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/21.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CShadedTriangle.h"

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
    
    shaderManager.InitializeStockShaders();
    
    // Load up a triangle
    GLfloat vVerts[] = { -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
						  0.0f, 0.5f, 0.0f };
    
    GLfloat vColors [] = { 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f };
    
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.CopyColorData4f(vColors);
    triangleBatch.End();
    
    myIdentityShader = gltLoadShaderPairWithAttributes(getFileName("ShadedIdentity.vp").c_str(), getFileName("ShadedIdentity.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_COLOR, "vColor");
    
    cout<<myIdentityShader<<endl;
}

void CShadedTriangle::ShutdownRC()
{
    glDeleteProgram(myIdentityShader);
}

void CShadedTriangle::defaultDisplayFunc()
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glUseProgram(gShadedTriangle->myIdentityShader);
    gShadedTriangle->triangleBatch.Draw();
    
    // Perform the buffer swap to display back buffer
    glutSwapBuffers();
}

















