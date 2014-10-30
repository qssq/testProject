//
//  COpenGlBase.h
//  MacOpenGl
//
//  Created by gongxun on 14/10/31.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGl__COpenGlBase__
#define __MacOpenGl__COpenGlBase__

#include <GLUT/glut.h>

class COpenGLBase
{
public:
    COpenGLBase();
    ~COpenGLBase();
    void run();
    
    void setDisplayFunc(void (*func)(void));
    void setReshapeFunc(void (*func)(int width, int height));
};


#endif /* defined(__MacOpenGl__COpenGlBase__) */
