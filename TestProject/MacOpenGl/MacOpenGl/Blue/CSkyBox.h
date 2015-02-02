//
//  CSkyBox.h
//  MacOpenGL
//
//  Created by gongxun on 15/1/29.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#ifndef __MacOpenGL__CSkyBox__
#define __MacOpenGL__CSkyBox__

#include "COpenGLBase.h"

class CSkyBox : public COpenGLBase
{
public:
    static CSkyBox *gSkyBox;
    CSkyBox(int argc, char *argv[]);
    ~CSkyBox();
    virtual void SetupRC();
    virtual void ShutdownRC();
    
    static void defaultDisplayFunc();
    static void defaultSpecialFunc(int key, int x, int y);
    
private:
    GLTriangleBatch     sphereBatch;
    GLBatch             cubeBatch;
    
    GLuint              cubeTexture;
    GLuint				tarnishTexture;
    
    GLint               reflectionShader;
    GLint               skyBoxShader;
    GLint               locMVPReflect, locMVReflect, locNormalReflect, locInvertedCamera;
    GLint				locMVPSkyBox;
    GLint				locCubeMap, locTarnishMap;
};

#endif /* defined(__MacOpenGL__CSkyBox__) */
