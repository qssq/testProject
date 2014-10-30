//
//  COpenGlBase.cpp
//  MacOpenGl
//
//  Created by gongxun on 14/10/31.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#include "COpenGLBase.h"

COpenGLBase::COpenGLBase()
{
    int argc = 1;
    char argb[] = {'G', 'X'};
    char *argv[] = {argb};
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("GongXun");
    
    glClearColor(0, 0, 0, 0);
    glShadeModel(GL_FLAT);
}

COpenGLBase::~COpenGLBase()
{
    
}

void COpenGLBase::run()
{
    glutMainLoop();
}

void COpenGLBase::setDisplayFunc(void (*func)(void))
{
    glutDisplayFunc(func);
}

void COpenGLBase::setReshapeFunc(void (*func)(int width, int height))
{
    glutReshapeFunc(func);
}