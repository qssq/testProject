//
//  COpenGlBase.h
//  MacOpenGl
//
//  Created by gongxun on 14/10/31.
//  Copyright (c) 2014年 gongxun. All rights reserved.
//

#ifndef __MacOpenGl__COpenGlBase__
#define __MacOpenGl__COpenGlBase__

#include "COpenGLFunc.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class COpenGLBase : public COpenGLFunc
{
public:
    COpenGLBase(int argc, char* argv[]);
    virtual ~COpenGLBase();
    void mainLoop();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void logMatrix44(const M3DMatrix44f &m);
    static void DrawWireFramedBatch(GLTriangleBatch* pBatch);
    bool LoadTGATexture(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum wrapMode);
    string getFileName(const char *fileName);
};


#endif /* defined(__MacOpenGl__COpenGlBase__) */
