//
//  CPointSprites.cpp
//  MacOpenGL
//
//  Created by gongxun on 15/2/2.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include "CPointSprites.h"
#include <StopWatch.h>

CPointSprites *CPointSprites::gPointSprites = nullptr;

CPointSprites::CPointSprites(int argc, char *argv[]) : COpenGLBase(argc, argv)
{
    gPointSprites = this;
    setDisplayFunc(CPointSprites::defaultDisplayFunc);
    setReshapeFunc(CPointSprites::defaultReshapeFunc);
}

CPointSprites::~CPointSprites()
{
    gPointSprites = nullptr;
}

void CPointSprites::SetupRC()
{
    // Background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
    // A number of shipping drivers are not conformant to the current OpenGL
    // spec and require this. NVidia... in particular. The OpenGL specification
    // states that this is always "on", in fact you can't enable or disable it
    // anymore. Adding this lines "fixes" this on non-conformant drivers, but
    // be aware, if you have a pure core (and working correctly) GL context,
    //you should not do this
    glEnable(GL_POINT_SPRITE);
    
    GLfloat fColors[4][4] = {{ 1.0f, 1.0f, 1.0f, 1.0f}, // White
        { 0.67f, 0.68f, 0.82f, 1.0f}, // Blue Stars
        { 1.0f, 0.5f, 0.5f, 1.0f}, // Reddish
        { 1.0f, 0.82f, 0.65f, 1.0f}}; // Orange
    
    
    // Randomly place the stars in their initial positions, and pick a random color
    starsBatch.Begin(GL_POINTS, NUM_STARS);
    for(int i = 0; i < NUM_STARS; i++)
    {
        int iColor = 0;		// All stars start as white
        
        // One in five will be blue
        if(rand() % 5 == 1)
            iColor = 1;
        
        // One in 50 red
        if(rand() % 50 == 1)
            iColor = 2;
        
        // One in 100 is amber
        if(rand() % 100 == 1)
            iColor = 3;
        
        
        starsBatch.Color4fv(fColors[iColor]);
        
        M3DVector3f vPosition;
        vPosition[0] = float(3000 - (rand() % 6000)) * 0.1f;
        vPosition[1] = float(3000 - (rand() % 6000)) * 0.1f;
        vPosition[2] = -float(rand() % 1000)-1.0f;  // -1 to -1000.0f
        
        starsBatch.Vertex3fv(vPosition);
    }
    starsBatch.End();
    
    
    starFieldShader = gltLoadShaderPairWithAttributes(getFileName("PointSprites/SpaceFlight.vp").c_str(), getFileName("PointSprites/SpaceFlight.fp").c_str(), 2, GLT_ATTRIBUTE_VERTEX, "vVertex",
                                                      GLT_ATTRIBUTE_COLOR, "vColor");
    
    locMVP = glGetUniformLocation(starFieldShader, "mvpMatrix");
    locTexture = glGetUniformLocation(starFieldShader, "starImage");
    locTimeStamp = glGetUniformLocation(starFieldShader, "timeStamp");
    
    glGenTextures(1, &starTexture);
    glBindTexture(GL_TEXTURE_2D, starTexture);
    LoadTGATexture(getFileName("PointSprites/Star.tga").c_str(), GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE);
}

void CPointSprites::ShutdownRC()
{
    glDeleteTextures(1, &starTexture);
}

void CPointSprites::defaultDisplayFunc()
{
    static CStopWatch timer;
    
    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Turn on additive blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    
    // Let the vertex program determine the point size
    glEnable(GL_PROGRAM_POINT_SIZE);
    
    // Bind to our shader, set uniforms
    glUseProgram(gPointSprites->starFieldShader);
    glUniformMatrix4fv(gPointSprites->locMVP, 1, GL_FALSE, gPointSprites->viewFrustum.GetProjectionMatrix());
    glUniform1i(gPointSprites->locTexture, 0);
    
    // fTime goes from 0.0 to 999.0 and recycles
    float fTime = timer.GetElapsedSeconds() * 10.0f;
    fTime = fmod(fTime, 999.0f);
    glUniform1f(gPointSprites->locTimeStamp, fTime);
    
    // Draw the stars
    gPointSprites->starsBatch.Draw();
    
    glutSwapBuffers();
    glutPostRedisplay();
}

void CPointSprites::defaultReshapeFunc(int width, int height)
{
    // Prevent a divide by zero
    if(height == 0)
        height = 1;
    
    // Set Viewport to window dimensions
    glViewport(0, 0, width, height);
    
    viewFrustum.SetPerspective(35.0f, float(width)/float(height), 1.0f, 1000.0f);
}
























