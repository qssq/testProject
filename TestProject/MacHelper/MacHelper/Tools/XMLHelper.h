//
//  XMLHelper.hpp
//  MacHelper
//
//  Created by gongxun on 16/6/13.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#ifndef XMLHelper_hpp
#define XMLHelper_hpp

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "CImageHandle.h"

using namespace std;

struct TexturePackerInfo
{
    string name;
    int x;
    int y;
    int width;
    int height;
    int offsetX;
    int offsetY;
    int offsetWidth;
    int offsetHeight;
    bool isRotated;
};

class XMLHelper
{
public:
    static XMLHelper *singleton();
    
    void test();
    void getTexturePackets(const string &file, vector<TexturePackerInfo> &infos);
    
    void getTexturePacketsKw(const string &file, vector<frameStruct> &frames);
    
    //特殊处理返回结构
    vector<frameStruct> getFrameStruct2(const string &file);
private:
    static XMLHelper *mXMLHelper;
    XMLHelper();
    ~XMLHelper();
};

#endif /* XMLHelper_hpp */
