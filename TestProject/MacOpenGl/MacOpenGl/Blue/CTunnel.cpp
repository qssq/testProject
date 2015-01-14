//
//  CTunnel.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/14.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CTunnel.h"

CTunnel *CTunnel::gTunnel = NULL;

CTunnel::CTunnel(int argc, char *argv[]) : COpenGLBase(argc, argv), mViewZ(-65.0f), mViewRotate(0.0f)
{
    gTunnel = this;
    
    setDisplayFunc(CTunnel::defaultDisplayFunc);
    setReshapeFunc(CTunnel::defaultReshapeFunc);
    setSpecialFunc(CTunnel::defaultSpecialFunc);
    
    glutCreateMenu(ProcessMenu);
    glutAddMenuEntry("GL_NEAREST",0);
    glutAddMenuEntry("GL_LINEAR",1);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_NEAREST",2);
    glutAddMenuEntry("GL_NEAREST_MIPMAP_LINEAR", 3);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_NEAREST", 4);
    glutAddMenuEntry("GL_LINEAR_MIPMAP_LINEAR", 5);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    mTextureFiles[0] = getFileName("brick.tga");
    mTextureFiles[1] = getFileName("floor.tga");
    mTextureFiles[2] = getFileName("ceiling.tga");
    
}

CTunnel::~CTunnel()
{
    gTunnel = NULL;
}

void CTunnel::SetupRC()
{
    CameraFrame.RotateWorld(float(m3dDegToRad(180.0f)), 0.0f, 1.0f, 0.0f);
    CameraFrame.MoveForward(-18.0f);
    
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    GLint iLoop;
    
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    
    shaderManager.InitializeStockShaders();
    
    // Load textures
    glGenTextures(TEXTURE_COUNT, mTextures);
    for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
    {
        // Bind to next texture object
        glBindTexture(GL_TEXTURE_2D, mTextures[iLoop]);
        
        // Load texture, set filter and wrap modes
        pBytes = gltReadTGABits(mTextureFiles[iLoop].c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
        
        // Load texture, set filter and wrap modes
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  //放大过滤器 最邻近过滤 线性过滤
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        //                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  //放大过滤器 最邻近过滤 线性过滤
        //                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
        glGenerateMipmap(GL_TEXTURE_2D);
        // Don't need original texture data any more
        free(pBytes);
    }
    // Build Geometry
    GLfloat z;
    floorBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for(z = 60.0f; z >= 0.0f; z -=10.0f)
    {
        floorBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        floorBatch.Vertex3f(-10.0f, -10.0f, z);
        
        floorBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        floorBatch.Vertex3f(10.0f, -10.0f, z);
        
        floorBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        floorBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);
        
        floorBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        floorBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);
    }
    floorBatch.End();
    
    ceilingBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for(z = 60.0f; z >= 0.0f; z -=10.0f)
    {
        ceilingBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        ceilingBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);
        
        ceilingBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        ceilingBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);
        
        ceilingBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        ceilingBatch.Vertex3f(-10.0f, 10.0f, z);
        
        ceilingBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        ceilingBatch.Vertex3f(10.0f, 10.0f, z);
    }
    ceilingBatch.End();
    
    leftWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for(z = 60.0f; z >= 0.0f; z -=10.0f)
    {
        leftWallBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        leftWallBatch.Vertex3f(-10.0f, -10.0f, z);
        
        leftWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        leftWallBatch.Vertex3f(-10.0f, 10.0f, z);
        
        leftWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        leftWallBatch.Vertex3f(-10.0f, -10.0f, z - 10.0f);
        
        leftWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        leftWallBatch.Vertex3f(-10.0f, 10.0f, z - 10.0f);
    }
    leftWallBatch.End();
    
    
    rightWallBatch.Begin(GL_TRIANGLE_STRIP, 28, 1);
    for(z = 60.0f; z >= 0.0f; z -=10.0f)
    {
        rightWallBatch.MultiTexCoord2f(0, 0.0f, 0.0f);
        rightWallBatch.Vertex3f(10.0f, -10.0f, z);
        
        rightWallBatch.MultiTexCoord2f(0, 0.0f, 1.0f);
        rightWallBatch.Vertex3f(10.0f, 10.0f, z);
        
        rightWallBatch.MultiTexCoord2f(0, 1.0f, 0.0f);
        rightWallBatch.Vertex3f(10.0f, -10.0f, z - 10.0f);
        
        rightWallBatch.MultiTexCoord2f(0, 1.0f, 1.0f);
        rightWallBatch.Vertex3f(10.0f, 10.0f, z - 10.0f);
    }
    rightWallBatch.End();
}

void CTunnel::ShutdownRC()
{
    glDeleteTextures(TEXTURE_COUNT, mTextures);
}

void CTunnel::defaultDisplayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    modelViewMatrix.PushMatrix();
    //摄像机
    M3DMatrix44f camera;
    CameraFrame.GetCameraMatrix(camera);
    modelViewMatrix.PushMatrix(camera);

    shaderManager.UseStockShader(GLT_SHADER_TEXTURE_REPLACE, transformPipeline.GetModelViewProjectionMatrix(), 0);
    
    glBindTexture(GL_TEXTURE_2D, gTunnel->mTextures[TEXTURE_FLOOR]);
    gTunnel->floorBatch.Draw();
    
    glBindTexture(GL_TEXTURE_2D, gTunnel->mTextures[TEXTURE_CEILING]);
    gTunnel->ceilingBatch.Draw();
    
    glBindTexture(GL_TEXTURE_2D, gTunnel->mTextures[TEXTURE_BRICK]);
    gTunnel->leftWallBatch.Draw();
    gTunnel->rightWallBatch.Draw();
    
    modelViewMatrix.PopMatrix();
    modelViewMatrix.PopMatrix();
    
    // Buffer swap
    glutSwapBuffers();
}

void CTunnel::defaultReshapeFunc(int w, int h)
{
    GLfloat fAspect;
    
    // Prevent a divide by zero
    if(h == 0)
        h = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);
    
    fAspect = (GLfloat)w/(GLfloat)h;
    
    // Produce the perspective projection
    viewFrustum.SetPerspective(80.0f, fAspect, 1.0, 200.0);
    projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());
    
    transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);
    
}

void CTunnel::defaultSpecialFunc(int key, int x, int y)
{
    float linear = 1.0f;
    float angular = float(m3dDegToRad(10.0f));
    
    if(key == GLUT_KEY_UP)
        CameraFrame.MoveForward(linear);
    
    if(key == GLUT_KEY_DOWN)
        CameraFrame.MoveForward(-linear);
    
    if(key == GLUT_KEY_LEFT)
        CameraFrame.RotateWorld(angular, 0.0f, 1.0f, 0.0f);
    
    if(key == GLUT_KEY_RIGHT)
        CameraFrame.RotateWorld(-angular, 0.0f, 1.0f, 0.0f);
    
    // Refresh the Window
    glutPostRedisplay();
}

void CTunnel::ProcessMenu(int value)
{
    GLint iLoop;
    
    for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
    {
        glBindTexture(GL_TEXTURE_2D, gTunnel->mTextures[iLoop]);
        
        switch(value)
        {
            case 0:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                break;
                
            case 1:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                break;
                
            case 2:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                break;
                
            case 3:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                break;
                
            case 4:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                break;
                
            case 5:
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                break;
        }
    }
    
    // Trigger Redraw
    glutPostRedisplay();
}
















