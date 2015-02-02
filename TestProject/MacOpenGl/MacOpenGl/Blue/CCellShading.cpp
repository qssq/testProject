//
//  CCellShading.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/27.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CCellShading.h"
#include <StopWatch.h>

CCellShading *CCellShading::gCellShading = NULL;

CCellShading::CCellShading(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gCellShading = this;
    setDisplayFunc(CCellShading::defaultDisplayFunc);
}

CCellShading::~CCellShading()
{
    gCellShading = NULL;
}

void CCellShading::SetupRC()
{
    // Background
    glClearColor(0.025f, 0.25f, 0.25f, 1.0f );
    
    glEnable(GL_DEPTH_TEST);
    
    shaderManager.InitializeStockShaders();
    viewFrame.MoveForward(4.0f);
    
    // Make the torus
    gltMakeTorus(torusBatch, 0.80f, 0.25f, 52, 26);
    
    toonShader = gltLoadShaderPairWithAttributes(getFileName("ToonShader.vp").c_str(), getFileName("ToonShader.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex",
                                                 GLT_ATTRIBUTE_NORMAL, "vNormal");
    
    locLight = glGetUniformLocation(toonShader, "vLightPosition");
    locMVP = glGetUniformLocation(toonShader, "mvpMatrix");
    locMV  = glGetUniformLocation(toonShader, "mvMatrix");
    locNM  = glGetUniformLocation(toonShader, "normalMatrix");
    locColorTable = glGetUniformLocation(toonShader, "colorTable");
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_1D, texture);
    GLubyte textureData[6][3] =
    {
        32, 0, 32,
        64, 0, 64,
        128, 0, 128,
        160, 0, 160,
        192, 0, 192,
        255, 0, 255
    };
    
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 6, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

}

void CCellShading::ShutdownRC()
{
    glDeleteTextures(1, &texture);
}

void CCellShading::defaultDisplayFunc()
{
    static CStopWatch rotTimer;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
    
    GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
    GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat vDiffuseColor[] = { 0.1f, 1.0f, 0.1f, 1.0f };
    GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glUseProgram(gCellShading->toonShader);
    glUniform3fv(gCellShading->locLight, 1, vEyeLight);
    glUniformMatrix4fv(gCellShading->locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix4fv(gCellShading->locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix3fv(gCellShading->locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    glUniform1i(gCellShading->locColorTable, 0);
    gCellShading->torusBatch.Draw();
    
    modelViewMatrix.PopMatrix();
    
    
    glutSwapBuffers();
    glutPostRedisplay();

}