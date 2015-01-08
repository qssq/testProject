//
//  Triangle.cpp
//  MacOpenGL
//
//  Created by gongxun on 14/11/10.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#include "Triangle.h"

Triangle::Triangle(int argc, char* argv[]) : COpenGLBase(argc, argv)
{
    setDisplayFunc(Triangle::defaultDisplayFunc);
}

Triangle::~Triangle()
{
    
}

void Triangle::SetupRC()
{
    
}

void Triangle::defaultDisplayFunc()
{
    glClearColor(0, 0, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glClearColor(1, 0, 0, 0);
    glScissor(100, 100, 600, 400);
    glEnable(GL_SCISSOR_TEST);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glDisable(GL_SCISSOR_TEST);
    glutSwapBuffers();
}