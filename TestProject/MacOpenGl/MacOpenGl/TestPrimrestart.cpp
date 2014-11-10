//
//  TestPrimrestart.cpp
//  MacOpenGL
//
//  Created by gongxun on 14/11/4.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#include "TestPrimrestart.h"
#include <iostream>

using namespace std;

#define BUFFER_OFFSET(offset)   ((GLvoid *) NULL + offset)

#define XStart                  -0.8
#define XEnd                    0.8
#define YStart                  -0.8
#define Yend                    0.8
#define NumXPoints              11
#define NumYPoints              11
#define NumPoints               (NumXPoints * NumXPoints)
#define NumPointsPerStrip       (2 * NumXPoints)
#define NumStrips               (NumYPoints - 1)
#define RestartIndex            0xffff

TestPrimrestart::TestPrimrestart()
{
    setDisplayFunc(TestPrimrestart::display);
    setReshapeFunc(TestPrimrestart::reshape);
    
    
    
    GLuint vbo, ebo;
    GLfloat *vertices;
    GLushort *indices;
    
    /* set up vertex data */
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * NumPoints * sizeof(GLfloat), NULL, GL_STATIC_DRAW);
    vertices = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    if (vertices == NULL)
    {
        cout<<"vertices失败了"<<endl;
        return;
    }
    else
    {
        int i,j;
        GLfloat dx = (XEnd - XStart) / (NumXPoints - 1);
        GLfloat dy = (Yend - YStart) / (NumYPoints - 1);
        GLfloat *tmp = vertices;
        int n = 0;
        
        for (j = 0; j < NumYPoints; ++j)
        {
            GLfloat y = YStart + j * dy;
            
            for (i = 0; i < NumXPoints; ++i)
            {
                GLfloat x = XStart + i *dx;
                *tmp++ = x;
                *tmp++ = y;
            }
        }
        
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glVertexPointer(2, GL_FLOAT, 0, 0);
        glEnableClientState(GL_VERTEX_ARRAY);
    }
    
    /* set up index data */
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    
    /* we allocate an extra restart index because it simplifies the element-array loop logic */
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NumStrips * (NumPointsPerStrip + 1) * sizeof(GLushort), NULL, GL_STATIC_DRAW);
    indices = (GLushort*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
    
    if (indices == NULL)
    {
        cout<<"indices失败了"<<endl;
    }
    else
    {
        int i, j;
        GLushort *index = indices;
        for (j = 0; j < NumStrips; ++j)
        {
            GLushort bottomRow = j * NumYPoints;
            GLushort topRow = bottomRow + NumYPoints;
            
            for (i = 0; i < NumXPoints; ++i)
            {
                *index++ = topRow + i;
                *index++ = bottomRow + i;
            }
            *index++ = RestartIndex;
        }
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
    }
    //glPrimitiveRestartIndex(RestartIndex);
}

TestPrimrestart::~TestPrimrestart()
{
    
}

void TestPrimrestart::display()
{
    
}

void TestPrimrestart::reshape(int width, int height)
{
    
}