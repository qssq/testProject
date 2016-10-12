//
//  GILHelper.h
//  MacHelper
//
//  Created by gongxun on 16/5/3.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#ifndef GILHelper_h
#define GILHelper_h

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct ImgRect
{
    int x;
    int y;
    int width;
    int height;
    int offsetX;
    int offsetY;
    int offsetWidth;
    int offsetHeight;
    bool isRotated;
    string name;
};

class CImgHelper
{
public:
    CImgHelper();
    ~CImgHelper();
    
    void test01();
    void GaussianBlur(const string &file);
    void CreateImage();
    void copyFile(const string &file);
    
    void texturePacker(const string &plist, const string &png);
private:
    string getFullName(const string &file);
    
    void copyFiles(const vector<ImgRect> &rects, const string &file);

    void copyLodingFiles();
    
    void copyTimerFiles();
    
    void copyChiFiles();
    
    void copyFishFiles();
    
    void createCards();
    
    void cleanWhite();
    
};

#endif /* GILHelper_h */
