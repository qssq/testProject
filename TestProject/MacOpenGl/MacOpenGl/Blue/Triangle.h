//
//  Triangle.h
//  MacOpenGL
//
//  Created by gongxun on 14/11/10.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__Triangle__
#define __MacOpenGL__Triangle__

#include "GLTools.h"
#include "GLShaderManager.h"

#include <iostream>
#include <glut/glut.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;

void ChangeSize(int w, int h)
{
    glViewport(0, 0, w, h);
}

void SetupRC()
{
    //blue background
    glClearColor(0, 0, 1, 1);
    
    shaderManager.InitializeStockShaders();
    
    //load up a triangle
    GLfloat vVerts[] = {
        -0.5f, 0, 0,
        0.5f, 0, 0,
        0, 0.5f, 0};
    
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
}

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    GLfloat vRed[] = {0.64f, 0.4f, 0.12f, 1};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    triangleBatch.Draw();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

GLfloat mCenterPoint[] ={0, 0};

void SpecialKeys(int key, int x, int y)
{
    GLfloat setpSize = 0.025f;
    
    GLfloat blockX = mCenterPoint[0];
    GLfloat blockY = mCenterPoint[1];
    
    if (key == GLUT_KEY_UP)
    {
        blockY += setpSize;
    }
    if (key == GLUT_KEY_DOWN)
    {
        blockY -= setpSize;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        blockX += setpSize;
    }
    if (key == GLUT_KEY_LEFT)
    {
        blockX -= setpSize;
    }
    
    if (blockX > 0.5f)
    {
        blockX = 0.5f;
    }
    else if (blockX < -0.5f)
    {
        blockX = -0.5f;
    }
    if (blockY > 0.5f)
    {
        blockY = 0.5f;
    }
    else if (blockY < -1)
    {
        blockY = -1;
    }
    
    mCenterPoint[0] = blockX;
    mCenterPoint[1] = blockY;
    
    GLfloat vVerts[] = {
        blockX - 0.5f, blockY, 0,
        blockX + 0.5f, blockY, 0,
        blockX, blockY + 0.5f, 0};
    
    triangleBatch.CopyVertexData3f(vVerts);
}

int start(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
    
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout<<"GLEW Error : "<<glewGetErrorString(err)<<std::endl;
        return 1;
    }
    
    SetupRC();
    
    glutMainLoop();
    
    return 0;
}


#endif /* defined(__MacOpenGL__Triangle__) */
