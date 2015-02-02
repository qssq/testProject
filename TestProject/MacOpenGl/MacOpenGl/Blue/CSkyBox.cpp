//
//  CSkyBox.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/1/29.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CSkyBox.h"

// Six sides of a cube map
const char *gSzCubeFaces[6] = { "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/pos_x.tga", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/neg_x.tga", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/pos_y.tga", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/neg_y.tga", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/pos_z.tga", "/Users/gongxun/GitHub/testProject/TestProject/MacOpenGL/Resources/CubeMapped/neg_z.tga" };

GLenum  gCube[6] = {  GL_TEXTURE_CUBE_MAP_POSITIVE_X,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
    GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
    GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

CSkyBox *CSkyBox::gSkyBox = NULL;

CSkyBox::CSkyBox(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gSkyBox = this;
    setDisplayFunc(CSkyBox::defaultDisplayFunc);
    setSpecialFunc(CSkyBox::defaultSpecialFunc);
}

CSkyBox::~CSkyBox()
{
    gSkyBox = NULL;
}

void CSkyBox::SetupRC()
{
    GLbyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    int i;
    
    // Cull backs of polygons
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    // Load the tarnish texture
    glGenTextures(1, &tarnishTexture);
    glBindTexture(GL_TEXTURE_2D, tarnishTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    pBytes = gltReadTGABits(getFileName("MultiTexture/tarnish.tga").c_str(), &iWidth, &iHeight, &iComponents, &eFormat);
    glTexImage2D(GL_TEXTURE_2D, 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
    free(pBytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // Load the cube map
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
    
    // Set up texture maps
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    // Load Cube Map images
    for(i = 0; i < 6; i++)
    {
        // Load this texture map
        pBytes = gltReadTGABits(gSzCubeFaces[i], &iWidth, &iHeight, &iComponents, &eFormat);
        glTexImage2D(gCube[i], 0, iComponents, iWidth, iHeight, 0, eFormat, GL_UNSIGNED_BYTE, pBytes);
        free(pBytes);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    
    viewFrame.MoveForward(-4.0f);
    gltMakeSphere(sphereBatch, 1.0f, 52, 26);
    gltMakeCube(cubeBatch, 20.0f);
    
    reflectionShader = gltLoadShaderPairWithAttributes(getFileName("MultiTexture/Reflection.vp").c_str(), getFileName("MultiTexture/Reflection.fp").c_str(), 3,
                                                       GLT_ATTRIBUTE_VERTEX, "vVertex",
                                                       GLT_ATTRIBUTE_NORMAL, "vNormal",
                                                       GLT_ATTRIBUTE_TEXTURE0, "vTexCoords");
    
    locMVPReflect = glGetUniformLocation(reflectionShader, "mvpMatrix");
    locMVReflect = glGetUniformLocation(reflectionShader, "mvMatrix");
    locNormalReflect = glGetUniformLocation(reflectionShader, "normalMatrix");
    locInvertedCamera = glGetUniformLocation(reflectionShader, "mInverseCamera");
    locCubeMap = glGetUniformLocation(reflectionShader, "cubeMap");
    locTarnishMap = glGetUniformLocation(reflectionShader, "tarnishMap");
    
    
    skyBoxShader = gltLoadShaderPairWithAttributes(getFileName("MultiTexture/SkyBox.vp").c_str(), getFileName("MultiTexture/SkyBox.fp").c_str(), 2,
                                                   GLT_ATTRIBUTE_VERTEX, "vVertex",
                                                   GLT_ATTRIBUTE_NORMAL, "vNormal");
    
    locMVPSkyBox = glGetUniformLocation(skyBoxShader, "mvpMatrix");
    
    // Set textures to their texture units
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tarnishTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
    
}

void CSkyBox::ShutdownRC()
{
    glDeleteTextures(1, &cubeTexture);
}

void CSkyBox::defaultDisplayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    M3DMatrix44f mCamera;
    M3DMatrix44f mCameraRotOnly;
    M3DMatrix44f mInverseCamera;
    
    viewFrame.GetCameraMatrix(mCamera, false);
    viewFrame.GetCameraMatrix(mCameraRotOnly, true);
    m3dInvertMatrix44(mInverseCamera, mCameraRotOnly);
    
    modelViewMatrix.PushMatrix();
    // Draw the sphere
    modelViewMatrix.MultMatrix(mCamera);
    glUseProgram(gSkyBox->reflectionShader);
    glUniformMatrix4fv(gSkyBox->locMVPReflect, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    glUniformMatrix4fv(gSkyBox->locMVReflect, 1, GL_FALSE, transformPipeline.GetModelViewMatrix());
    glUniformMatrix3fv(gSkyBox->locNormalReflect, 1, GL_FALSE, transformPipeline.GetNormalMatrix());
    glUniformMatrix4fv(gSkyBox->locInvertedCamera, 1, GL_FALSE, mInverseCamera);
    glUniform1i(gSkyBox->locCubeMap, 0);
    glUniform1i(gSkyBox->locTarnishMap, 1);
    
    glEnable(GL_CULL_FACE);
    gSkyBox->sphereBatch.Draw();
    glDisable(GL_CULL_FACE);
    modelViewMatrix.PopMatrix();
    
    modelViewMatrix.PushMatrix();
    modelViewMatrix.MultMatrix(mCameraRotOnly);
    glUseProgram(gSkyBox->skyBoxShader);
    glUniformMatrix4fv(gSkyBox->locMVPSkyBox, 1, GL_FALSE, transformPipeline.GetModelViewProjectionMatrix());
    gSkyBox->cubeBatch.Draw();
    modelViewMatrix.PopMatrix();
    
    // Do the buffer Swap
    glutSwapBuffers();
}

void CSkyBox::defaultSpecialFunc(int key, int x, int y)
{
    if(key == GLUT_KEY_UP)
        viewFrame.MoveForward(0.1f);
    
    if(key == GLUT_KEY_DOWN)
        viewFrame.MoveForward(-0.1f);
    
    if(key == GLUT_KEY_LEFT)
        viewFrame.MoveRight(-0.1);
    
    if(key == GLUT_KEY_RIGHT)
        viewFrame.MoveRight(0.1);
    
    // Refresh the Window
    glutPostRedisplay();

}















