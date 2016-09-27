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
    int sizeWidth;
    int sizeHeight;
    bool isRotated;
};

class XMLHelper
{
public:
    static XMLHelper *singleton();
    
    void test();
    void getTexturePackets(const string &file, vector<TexturePackerInfo> &infos);
private:
    static XMLHelper *mXMLHelper;
    XMLHelper();
    ~XMLHelper();
};

#endif /* XMLHelper_hpp */
