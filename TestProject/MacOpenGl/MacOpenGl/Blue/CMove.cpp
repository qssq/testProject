//
//  CMove.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/6.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CMove.h"

GLBatch	CMove::squareBatch;

GLfloat CMove::xPos = 0.0f;
GLfloat CMove::yPos = 0.0f;
GLfloat CMove::blockSize = 0.1f;

CMove::CMove(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    setDisplayFunc(CMove::defaultDisplayFunc);
    setReshapeFunc(CMove::defaultReshapeFunc);
    setSpecialFunc(CMove::defaultSpecialFunc);
}

CMove::~CMove()
{
    
}

void CMove::SetupRC()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
    shaderManager.InitializeStockShaders();
    
    
    GLfloat blockSize = 0.1f;
    GLfloat vVerts[] = { -blockSize, -blockSize, 0.0f,
        blockSize, -blockSize, 0.0f,
        blockSize,  blockSize, 0.0f,
        -blockSize,  blockSize, 0.0f};
    
    // Load up a triangle
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}

void CMove::defaultDisplayFunc()
{
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    GLfloat vRed[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    M3DMatrix44f mFinalTransform, mTranslationMatrix, mRotationMatrix;
    
    // Just Translate
    m3dTranslationMatrix44(mTranslationMatrix, xPos, yPos, 0);
    logMatrix44(mTranslationMatrix);
    
    // Rotate 5 degrees evertyime we redraw
    static float yRot = 0.0f;
    yRot += 5.0f;
    m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(yRot), 0.0f, 0.0f, 1.0f);
    logMatrix44(mRotationMatrix);
    
    m3dMatrixMultiply44(mFinalTransform, mTranslationMatrix, mRotationMatrix);
    
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vRed);
    squareBatch.Draw();
    
    // Perform the buffer swap
    glutSwapBuffers();
}

void CMove::defaultReshapeFunc(int width, int height)
{
    glViewport(0, 0, width, height);
}

void CMove::defaultSpecialFunc(int key, int x, int y)
{
    GLfloat stepSize = 0.025f;
    
    
    if(key == GLUT_KEY_UP)
        yPos += stepSize;
    
    if(key == GLUT_KEY_DOWN)
        yPos -= stepSize;
    
    if(key == GLUT_KEY_LEFT)
        xPos -= stepSize;
    
    if(key == GLUT_KEY_RIGHT)
        xPos += stepSize;
    
    // Collision detection
    if(xPos < (-1.0f + blockSize)) xPos = -1.0f + blockSize;
    
    if(xPos > (1.0f - blockSize)) xPos = 1.0f - blockSize;
    
    if(yPos < (-1.0f + blockSize))  yPos = -1.0f + blockSize;
    
    if(yPos > (1.0f - blockSize)) yPos = 1.0f - blockSize;
    
    glutPostRedisplay();
}