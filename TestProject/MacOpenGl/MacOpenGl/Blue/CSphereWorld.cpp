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
    glEnable(GL_CULL_FACE);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    glClearColor(0, 0, 0, 1);
    
    //torus
    gltMakeTorus(gSphereWorld->mTorusBatch, 0.4, 0.15, 30, 30);
    
    // This make a sphere
    gltMakeSphere(gSphereWorld->mSphereBatch, 0.1f, 26, 13);
    
    /* 纹理
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
    
    */
    
    GLBatch &floorBatch =  gSphereWorld->mFloorBatch;
    GLfloat texSize = 10.0f;
    floorBatch.Begin(GL_TRIANGLE_FAN, 4, 1);
    floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
    floorBatch.Vertex3f(-20.0f, -0.41f, 20.0f);
    
    floorBatch.MultiTexCoord2f(0, texSize, 0.0f);
    floorBatch.Vertex3f(20.0f, -0.41f, 20.0f);
    
    floorBatch.MultiTexCoord2f(0, texSize, texSize);
    floorBatch.Vertex3f(20.0f, -0.41f, -20.0f);
    
    floorBatch.MultiTexCoord2f(0, 0.0f, texSize);
    floorBatch.Vertex3f(-20.0f, -0.41f, -20.0f);
    floorBatch.End();
    
    // Make 3 texture objects
    glGenTextures(3, mUiTextures);
    
    // Load the Marble
    glBindTexture(GL_TEXTURE_2D, mUiTextures[0]);
    LoadTGATexture(getFileName("marble.tga").c_str(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_REPEAT);
    
    // Load Mars
    glBindTexture(GL_TEXTURE_2D, mUiTextures[1]);
    LoadTGATexture(getFileName("marslike.tga").c_str(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    
    // Load Moon
    glBindTexture(GL_TEXTURE_2D, mUiTextures[2]);
    LoadTGATexture(getFileName("moonlike.tga").c_str(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
    
    //spheres
    for (int i = 0; i < spheresCount; ++i)
    {
        GLfloat x = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        GLfloat z = ((GLfloat)((rand() % 400) - 200) * 0.1f);
        mSpheres[i].SetOrigin(x, 0.0f, z);
    }
}

void CSphereWorld::ShutdownRC()
{
    glDeleteTextures(3, mUiTextures);
}

void CSphereWorld::DrawSongAndDance(GLfloat yRot)
{
    static GLfloat vWhite[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static GLfloat vLightPos[] = { 3.0f, 3.0f, 0.0f, 1.0f };
    
    // Get the light position in eye space
    M3DVector4f	vLightTransformed;
    M3DMatrix44f mCamera;
    modelViewMatrix.GetMatrix(mCamera);
    m3dTransformVector4(vLightTransformed, vLightPos, mCamera);
    
    // Draw the light source
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Translatev(vLightPos);
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vWhite);
    //画光源 月亮嘎嘎
    gSphereWorld->mSphereBatch.Draw();
    modelViewMatrix.PopMatrix();
    
    //用纹理 画随机的球
    glBindTexture(GL_TEXTURE_2D, gSphereWorld->mUiTextures[2]);
    for(int i = 0; i < spheresCount; i++)
    {
        modelViewMatrix.PushMatrix();
        modelViewMatrix.MultMatrix(gSphereWorld->mSpheres[i]);
        shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF,modelViewMatrix.GetMatrix(), transformPipeline.GetProjectionMatrix(), vLightTransformed, vWhite, 0);
        gSphereWorld->mSphereBatch.Draw();
        modelViewMatrix.PopMatrix();
    }
    
    // Song and dance
    modelViewMatrix.Translate(0.0f, 0.2f, -2.5f);
    //保存位移矩阵
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    
    // Draw stuff relative to the camera
    glBindTexture(GL_TEXTURE_2D, gSphereWorld->mUiTextures[1]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(), transformPipeline.GetProjectionMatrix(), vLightTransformed, vWhite, 0);
    gSphereWorld->mTorusBatch.Draw();
    //回到位移矩阵
    modelViewMatrix.PopMatrix();
    
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    
    glBindTexture(GL_TEXTURE_2D, gSphereWorld->mUiTextures[2]);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_POINT_LIGHT_DIFF, modelViewMatrix.GetMatrix(), transformPipeline.GetProjectionMatrix(), vLightTransformed, vWhite, 0);
    gSphereWorld->mSphereBatch.Draw();
}

void CSphereWorld::defaultDisplayFunc()
{
    // Color values
    static GLfloat vFloorColor[] = { 1.0f, 1.0f, 1.0f, 0.75f};
    
    static CStopWatch	rotTimer;
    float yRot = rotTimer.GetElapsedSeconds() * 60.0f;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //保存单位矩阵
    modelViewMatrix.PushMatrix();
    
    //摄像机
    M3DMatrix44f camera;
    CameraFrame.GetCameraMatrix(camera);
    modelViewMatrix.MultMatrix(camera);
    
    //翻转世界
    modelViewMatrix.PushMatrix();
    modelViewMatrix.Scale(1.0f, -1.0f, 1.0f);
    modelViewMatrix.Translate(0.0f, 0.8f, 0.0f); // Scootch the world down a bit...
    //现实正方形的背面
    glFrontFace(GL_CW);
    gSphereWorld->DrawSongAndDance(yRot);
    glFrontFace(GL_CCW);
    //翻转回来
    modelViewMatrix.PopMatrix();
    
    //画背景 和倒影混合
    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, gSphereWorld->mUiTextures[0]);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_MODULATE, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor, 0);
    
    gSphereWorld->mFloorBatch.Draw();
    glDisable(GL_BLEND);
    
    gSphereWorld->DrawSongAndDance(yRot);
    
    modelViewMatrix.PopMatrix();
    
    // Do the buffer Swap
    glutSwapBuffers();
    
    // Do it again
    glutPostRedisplay();
    /* 纹理
     static GLfloat vTorusColor[] = { 1.0f, 0.8f, 0.8f, 1.0f };
     static GLfloat vSphereColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    //光源
    M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
    M3DVector4f vLightEyePos;
    m3dTransformVector4(vLightEyePos, vLightPos, camera);
    
    //地板
    shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vFloorColor);
    gSphereWorld->mFloorBatch.Draw();
    
    //小球
    for(int i = 0; i < spheresCount; ++i)
    {
        modelViewMatrix.PushMatrix();
        modelViewMatrix.MultMatrix(gSphereWorld->mSpheres[i]);
        shaderManager.UseStockShader(GLT_SHADER_FLAT, transformPipeline.GetModelViewProjectionMatrix(), vSphereColor);
        gSphereWorld->mSphereBatch.Draw();
        modelViewMatrix.PopMatrix();
    }
    
    modelViewMatrix.Translate(0.0f, 0.0f, -2.5f);
    
    //保存平移
    modelViewMatrix.PushMatrix();
    
    modelViewMatrix.Rotate(yRot, 0.0f, 1.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightEyePos, vTorusColor);
    
    gSphereWorld->mTorusBatch.Draw();
    
    //消除旋转
    modelViewMatrix.PopMatrix();
    
    modelViewMatrix.Rotate(yRot * -2.0f, 0.0f, 1.0f, 0.0f);
    modelViewMatrix.Translate(0.8f, 0.0f, 0.0f);
    shaderManager.UseStockShader(GLT_SHADER_POINT_LIGHT_DIFF, transformPipeline.GetModelViewMatrix(), transformPipeline.GetProjectionMatrix(), vLightEyePos, vSphereColor);
    
    gSphereWorld->mSphereBatch.Draw();
    
    //消除平移
    modelViewMatrix.PopMatrix();
    //消除摄像机
    modelViewMatrix.PopMatrix();

    // Do the buffer Swap
    glutSwapBuffers();
    
    // Tell GLUT to do it again
    glutPostRedisplay();
     */
}

void CSphereWorld::defaultReshapeFunc(int width, int height)
{
    glViewport(0, 0, width, height);
    viewFrustum.SetPerspective(35, (float)width/(float)height, 1, 500);
    
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
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
    float linear = 0.2f;
    float angular = float(m3dDegToRad(10.0f));
    if(key == GLUT_KEY_UP)
        CameraFrame.MoveForward(linear);
    
    if(key == GLUT_KEY_DOWN)
        CameraFrame.MoveForward(-linear);
    
    if(key == GLUT_KEY_LEFT)
        CameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        CameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
}














