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

using namespace Plist;

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

//清除符号
inline string getCleanString(const string &s, const char &rechar)
{
    string result = s;
    string::size_type pos = 0;
    while ((pos = result.find(rechar, pos)) != string::npos)
    {
        result.replace(pos, 1, "");
    }
    return result;
}

//切分
inline vector<string>& split( const string& ori , char ch , vector<string>& ans )
{
    istringstream iss(ori);
    string item;
    while(getline(iss , item , ch)) ans.push_back(item);
    return ans;
}

inline vector<string> split( const string& ori , char ch )
{
    vector<string> ans;
    split(ori , ch , ans);
    return ans;
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
        
        int x, y, width, height, offsetX, offsetY, sizeWidth, sizeHeight;
        
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
        ss>>width;
        
        ss.str("");
        ss.clear();
        ss<<texts[3];
        ss>>height;
        
        //sourceColorRect
        offset = getCleanString(offset, '{');
        offset = getCleanString(offset, '}');
        texts = split(offset, ',');
        
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
        ss>>sizeWidth;
        
        ss.str("");
        ss.clear();
        ss<<texts[1];
        ss>>sizeHeight;
        
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
        info.sizeWidth = sizeWidth;
        info.sizeHeight = sizeHeight;
        
        infos.push_back(info);
    }
}























