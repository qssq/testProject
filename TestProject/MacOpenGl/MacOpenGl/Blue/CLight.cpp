//
//  CLight.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/26.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CLight.h"
#include <StopWatch.h>

CLight *CLight::gLight = NULL;

CLight::CLight(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    setDisplayFunc(CLight::defaultDisplayFunc);
    gLight = this;
}

CLight::~CLight()
{
    gLight = NULL;
}

void CLight::SetupRC()
{
    // Background
    glClearColor(0.3f, 0.3f, 0.3f, 1.0f );
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    viewFrame.MoveForward(4.0f);
    
    // Make the sphere
    gltMakeSphere(torusBatch, 1.0f, 26, 13);
    
    diffuseLightShader = gltLoadShaderPairWithAttributes(getFileName("test/light.vp").c_str(), getFileName("test/light.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
    
    locAmbient = glGetUniformLocation(diffuseLightShader, "ambientColor");
    locDiffuse = glGetUniformLocation(diffuseLightShader, "diffuseColor");
    locSpecular = glGetUniformLocation(diffuseLightShader, "specularColor");
    locLight = glGetUniformLocation(diffuseLightShader, "vLightPosition");
    locMVP = glGetUniformLocation(diffuseLightShader, "mvpMatrix");
    locMV  = glGetUniformLocation(diffuseLightShader, "mvMatrix");
    locNM  = glGetUniformLocation(diffuseLightShader, "normalMatrix");}

void CLight::ShutdownRC()
{
    glDeleteProgram(diffuseLightShader);
}

void CLight::defaultDisplayFunc()
{
    static CStopWatch rotTimer;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
    
    static GLfloat vLightPos[] = { 3.0f, 3.0f, 0.0f, 1.0f };
    GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };

    // Get the light position in eye space
//    M3DVector4f	vLightTransformed;
//    M3DMatrix44f mCamera;
//    modelViewMatrix.GetMatrix(mCamera);
//    m3dTransformVector4(vLightTransformed, vLightPos, mCamera);
//    
//    
//    GLfloat vEyeLight[] = {vLightTransformed[0]/vLightTransformed[3], vLightTransformed[1]/vLightTransformed[3], vLightTransformed[2]/vLightTransformed[3]};
    
    GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat vDiffuseColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glUseProgram(gLight->diffuseLightShader);
    glUniform4fv(gLight->locAmbient, 1, vAmbientColor);
    glUniform4fv(gLight->locDiffuse, 1, vDiffuseColor);
    glUniform4fv(gLight->locSpecular, 1, vSpecularColor);
    glUniform3fv(gLight->locLight, 1, vEyeLight);
    glUniformMatrix4fv(gLight->locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix4fv(gLight->locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix3fv(gLight->locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    gLight->torusBatch.Draw();
    
    modelViewMatrix.PopMatrix();
    
    
    glutSwapBuffers();
    glutPostRedisplay();

}





