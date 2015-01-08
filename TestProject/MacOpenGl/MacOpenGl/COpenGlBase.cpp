//
//  COpenGlBase.cpp
//  MacOpenGl
//
//  Created by gongxun on 14/10/31.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#include "COpenGLBase.h"
#include <iostream>

using namespace std;

COpenGLBase::COpenGLBase(int argc, char* argv[])
{
    gltSetWorkingDirectory(argv[0]);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GongXun");
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
    }
    
    setDefaultFunc();
}

COpenGLBase::~COpenGLBase()
{
    
}

void COpenGLBase::mainLoop()
{
    setFunc();
    SetupRC();
    glutMainLoop();
}

void COpenGLBase::SetupRC()
{
    
}

void COpenGLBase::logMatrix44(const M3DMatrix44f &m)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << m[i + (j * 4)] << " ";
        }
        cout<<endl;
    }
}

void COpenGLBase::DrawWireFramedBatch(GLTriangleBatch* pBatch)
{
    GLfloat vGreen[] = { 1.0f, 0.8f, 0.8f, 1.0f };
    
    GLfloat vBlack[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vGreen);
    pBatch->Draw();
    
    // Draw black outline
    glPolygonOffset(-1.0f, -1.0f);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(2.5f);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vBlack);
    pBatch->Draw();
    
    // Restore polygon mode and depht testing
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_POLYGON_OFFSET_LINE);
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
}



















