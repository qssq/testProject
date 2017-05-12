//
//  XMLHelper.cpp
//  MacHelper
//
//  Created by gongxun on 16/6/13.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "XMLHelper.h"
#include "Plist.hpp"
#include <strstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "Defines.h"

using namespace Plist;
namespace fs = boost::filesystem;

XMLHelper *XMLHelper::mXMLHelper = nullptr;

XMLHelper::XMLHelper()
{
    
}

XMLHelper::~XMLHelper()
{
    
}

XMLHelper *XMLHelper::singleton()
{
    if (!mXMLHelper)
    {
        mXMLHelper = new XMLHelper();
    }
    
    return mXMLHelper;
}

void XMLHelper::test()
{
    string gPath = "/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/";
    string file =gPath + "userHead.plist";
    
    map<string, boost::any> dict;
    Plist::readPlist(file.c_str(), dict);
    
    const dictionary_type& plistDic = boost::any_cast<const dictionary_type&>(dict.find("frames")->second);
    
    for(auto it=plistDic.begin();it!=plistDic.end();++it)
    {
        cout<<"key: "<<it->first <<endl;
        const dictionary_type& temp = boost::any_cast<const dictionary_type&>(it->second);
        const string& frame = boost::any_cast<const string&>(temp.find("frame")->second);
        cout<<"frame :" << frame<<endl;
    }
}

void XMLHelper::getTexturePackets(const string &file, vector<TexturePackerInfo> &infos)
{
    map<string, boost::any> dict;
    Plist::readPlist(file.c_str(), dict);
    
    const dictionary_type& plistDic = boost::any_cast<const dictionary_type&>(dict.find("frames")->second);
    
    for(auto it=plistDic.begin();it!=plistDic.end();++it)
    {
        
        cout<<"key: "<<it->first <<endl;
        const dictionary_type& temp = boost::any_cast<const dictionary_type&>(it->second);
        
        string frame = boost::any_cast<const string&>(temp.find("frame")->second);
        string sourceColorRect = boost::any_cast<const string&>(temp.find("sourceColorRect")->second);
        string sourceSize = boost::any_cast<const string&>(temp.find("sourceSize")->second);
        string offset = boost::any_cast<const string&>(temp.find("offset")->second);
        bool isRotated = boost::any_cast<const bool&>(temp.find("rotated")->second);
        
//        string frame = boost::any_cast<const string&>(temp.find("textureRect")->second);
//        bool isRotated = boost::any_cast<const bool&>(temp.find("textureRotated")->second);
//        isRotated = false;
        
        cout<<"frame :" << frame<<endl;
        
        
        TexturePackerInfo info;
        string name = split(it->first, '.').front();
        info.name = name;
        
        info.isRotated = isRotated;
        
        int x, y, width, height, offsetX, offsetY, offsetWidth, offsetHeight;
        
        //frame
        frame = getCleanString(frame, '{');
        frame = getCleanString(frame, '}');
        vector<string> texts = split(frame, ',');
        stringstream ss;
        
        ss.str("");
        ss.clear();
        ss<<texts[0];
        ss>>x;
        
        ss.str("");
        ss.clear();
        ss<<texts[1];
        ss>>y;
        
        ss.str("");
        ss.clear();
        ss<<texts[2];
        ss>>offsetWidth;
        
        ss.str("");
        ss.clear();
        ss<<texts[3];
        ss>>offsetHeight;
        
        //sourceColorRect
        sourceColorRect = getCleanString(sourceColorRect, '{');
        sourceColorRect = getCleanString(sourceColorRect, '}');
        texts = split(sourceColorRect, ',');
        
        ss.str("");
        ss.clear();
        ss<<texts[0];
        ss>>offsetX;
        
        ss.str("");
        ss.clear();
        ss<<texts[1];
        ss>>offsetY;
        
        //sourceSize
        sourceSize = getCleanString(sourceSize, '{');
        sourceSize = getCleanString(sourceSize, '}');
        texts = split(sourceSize, ',');
        
        ss.str("");
        ss.clear();
        ss<<texts[0];
        ss>>width;
        
        ss.str("");
        ss.clear();
        ss<<texts[1];
        ss>>height;
        
        if (width == 0 || height == 0)
        {
            continue;
        }
        info.x = x;
        info.y = y;
//        info.width = isRotated ? height : width;
//        info.height = isRotated ? width : height;
//        info.offsetX = isRotated ? offsetY : offsetX;
//        info.offsetY = isRotated ? offsetX : offsetY;
//        info.offsetWidth = isRotated ? offsetHeight : offsetWidth;
//        info.offsetHeight = isRotated ? offsetWidth : offsetHeight;
        info.width = width;
        info.height = height;
        info.offsetX = offsetX;
        info.offsetY = offsetY;
        info.offsetWidth = offsetWidth;
        info.offsetHeight = offsetHeight;
        
        infos.push_back(info);
    }
}

void XMLHelper::getTexturePacketsKw(const string &file, vector<frameStruct> &frames)
{
    map<string, boost::any> dict;
    Plist::readPlist(file.c_str(), dict);

    const dictionary_type& plistDic = boost::any_cast<const dictionary_type&>(dict.find("frames")->second);
    for(auto it = plistDic.begin(); it != plistDic.end(); ++it)
    {
        frameStruct frame;
        
        //rect
        const dictionary_type& temp = boost::any_cast<const dictionary_type&>(it->second);
        string textureRect = boost::any_cast<const string&>(temp.find("textureRect")->second);
        textureRect = getCleanString(textureRect, '{');
        textureRect = getCleanString(textureRect, '}');
        vector<string> rectStr = split(textureRect, ',');
        frame.x = getIntForString(rectStr[0]);
        frame.y = getIntForString(rectStr[1]);
        frame.w = getIntForString(rectStr[2]);
        frame.h = getIntForString(rectStr[3]);
        
        //textureRotated
        bool isRotated = boost::any_cast<const bool&>(temp.find("textureRotated")->second);
        frame.rotated = isRotated;
        
        //name
        string name = split(it->first, '.').front();
        frame.name = name;
        
        
        frames.push_back(frame);
    }
}

vector<frameStruct> XMLHelper::getFrameStruct2(const string &file)
{
    vector<frameStruct> reuslt;
    
    fs::path p(file);
    
    fs::ifstream ifile;
    ifile.open(p);
    
    vector<string> spriteSourceSizes;
    vector<string> names;
    string s;
    while (getline(ifile, s))
    {
        string findKey = "{\"frame\":{";
        size_t nameStart = 0;
        size_t end = 0;
        while (true)
        {
            nameStart = s.find(findKey, end);
            if (nameStart == string::npos)
            {
                break;
            }
            size_t start = nameStart + findKey.size();
            end = s.find("}", start);
            spriteSourceSizes.push_back(s.substr(start, end - start));
            
            string nickKey = "\"";
            size_t nickEnd = s.rfind(".png\"", nameStart);
            size_t nickStart = s.rfind(nickKey, nickEnd);
            names.push_back(s.substr(nickStart + nickKey.size(), nickEnd - nickStart - nickKey.size()));
        }
    }
    
    for (auto i = 0; i < spriteSourceSizes.size(); ++i)
    {
        frameStruct frame;
        frame.rotated = false;
        frame.name = names[i];
        
        string str = spriteSourceSizes[i];
        string key = "\"x\":";
        str = str.replace(str.find(key), key.size(), "");
        key = "\"y\":";
        str = str.replace(str.find(key), key.size(), "");
        key = "\"w\":";
        str = str.replace(str.find(key), key.size(), "");
        key = "\"h\":";
        str = str.replace(str.find(key), key.size(), "");
        
        vector<string> rectStr = split(str, ',');
        frame.x = getIntForString(rectStr[0]);
        frame.y = getIntForString(rectStr[1]);
        frame.w = getIntForString(rectStr[2]);
        frame.h = getIntForString(rectStr[3]);
        
        reuslt.push_back(frame);
    }
    
    return reuslt;
}



















