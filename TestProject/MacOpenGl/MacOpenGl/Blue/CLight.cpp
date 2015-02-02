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
    
//        diffuseLightShader = gltLoadShaderPairWithAttributes(getFileName("test/light_ASDGouraud.vp").c_str(), getFileName("test/light_ASDGouraud.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
//    diffuseLightShader = gltLoadShaderPairWithAttributes(getFileName("test/light_ADSPhong.vp").c_str(), getFileName("test/light_ADSPhong.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal");
    diffuseLightShader = gltLoadShaderPairWithAttributes(getFileName("test/ADSTexture.vp").c_str(), getFileName("test/ADSTexture.fp").c_str(), 3, GLT_ATTRIBUTE_VERTEX, "vVertex", GLT_ATTRIBUTE_NORMAL, "vNormal", GLT_ATTRIBUTE_TEXTURE0, "vTexture0");
    
    locAmbient = glGetUniformLocation(diffuseLightShader, "ambientColor");
    locDiffuse = glGetUniformLocation(diffuseLightShader, "diffuseColor");
    locSpecular = glGetUniformLocation(diffuseLightShader, "specularColor");
    locLight = glGetUniformLocation(diffuseLightShader, "vLightPosition");
    locMVP = glGetUniformLocation(diffuseLightShader, "mvpMatrix");
    locMV  = glGetUniformLocation(diffuseLightShader, "mvMatrix");
    locNM  = glGetUniformLocation(diffuseLightShader, "normalMatrix");
    locTexture = glGetUniformLocation(diffuseLightShader, "colorMap");
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    LoadTGATexture(getFileName("test/CoolTexture.tga").c_str(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

void CLight::ShutdownRC()
{
    glDeleteProgram(diffuseLightShader);
    glDeleteTextures(1, &texture);
}

void CLight::defaultDisplayFunc()
{
    static CStopWatch rotTimer;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix(viewFrame);
    modelViewMatrix.Rotate(rotTimer.GetElapsedSeconds() * 10.0f, 0.0f, 1.0f, 0.0f);
    GLfloat vEyeLight[] = { -100.0f, 100.0f, 100.0f };
    
    static GLfloat vLightPos[] = { 3.0f, 3.0f, 0.0f, 1.0f };

    // Get the light position in eye space
//    M3DVector4f	vLightTransformed;
//    M3DMatrix44f mCamera;
//    modelViewMatrix.GetMatrix(mCamera);
//    m3dTransformVector4(vLightTransformed, vLightPos, mCamera);
//    GLfloat vEyeLight[] = {vLightTransformed[0]/vLightTransformed[3], vLightTransformed[1]/vLightTransformed[3], vLightTransformed[2]/vLightTransformed[3]};
    
    GLfloat vAmbientColor[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat vDiffuseColor[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat vSpecularColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glBindTexture(GL_TEXTURE_2D, gLight->texture);
    glUseProgram(gLight->diffuseLightShader);
    glUniform4fv(gLight->locAmbient, 1, vAmbientColor);
    glUniform4fv(gLight->locDiffuse, 1, vDiffuseColor);
    glUniform4fv(gLight->locSpecular, 1, vSpecularColor);
    glUniform3fv(gLight->locLight, 1, vEyeLight);
    glUniformMatrix4fv(gLight->locMVP, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix4fv(gLight->locMV, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix3fv(gLight->locNM, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    glUniform1i(gLight->locTexture, 0);
    
    gLight->torusBatch.Draw();
    
    modelViewMatrix.PopMatrix();
    
    
    glutSwapBuffers();
    glutPostRedisplay();

}





