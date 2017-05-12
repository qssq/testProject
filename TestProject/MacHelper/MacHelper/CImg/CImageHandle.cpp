//
//  CImageHandle.cpp
//  MacHelper
//
//  Created by gongxun on 17/3/6.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "CImageHandle.h"
#include "CImg.h"
#include "png.h"
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include "XMLHelper.h"

using namespace std;
namespace fs = boost::filesystem;
using namespace cimg_library;

#define cimg_use_png

const string gPath = "/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/";

CImageHandle::CImageHandle()
{
    cimg::imagemagick_path("/usr/local/bin/convert");
}

CImageHandle::~CImageHandle()
{
    
}

void CImageHandle::handler()
{
    map<string, string> results;
//    results["86804832"] = "bcf65410";
//    results["3d49b31a"] = "7e4a7fa5";
//    results["9becc1ce"] = "676fcc00";
//    results["05d63ff4"] = "39045507";
    //    results["451e8111"] = "2eb1d6ed";
//    results["19a13bc2"] = "22610156";
//    results["24c92ec0"] = "92e1d433";
//    results["605481e1"] = "0b63865f";
//    results["0a746b46"] = "9ba9d34e";
    //    results["8c224c53"] = "1e5c129e";
        results["9d89cd6d"] = "b4d67045";
    
    for(auto it : results)
    {
        vector<frameStruct> rects = getFrameStruct(getFullName("jgkwx/" + it.first));
        copyFiles(rects, getFullName("jgkwx/" + it.second), "");
    }
}

void CImageHandle::handlerKw()
{
    map<string, string> results;
    //    results["game_base.plist"] = "game_base.png";
    results["ttz_base.plist"] = "ttz_base.png";
    results["com_dialog_new_texture.plist"] = "com_dialog_new_texture.png";
    
    for(auto it : results)
    {
        vector<frameStruct> rects;
        XMLHelper::singleton()->getTexturePacketsKw(getFullName("kwmj/" + it.first), rects);
        
        copyFiles(rects, getFullName("kwmj/" + it.second), "ttz/");
    }
}

string CImageHandle::getFullName(const string &file)
{
    return gPath + file;
}

void CImageHandle::copyFiles(const vector<frameStruct> &rects, const string &file, const string &path)
{
    cout<<"开始复制文件"<<endl;
    CImg<unsigned char> imgSource(file.c_str());
    for (auto it : rects)
    {
        if (!it.rotated)
        {
            int x = it.x;
            int y = it.y;
            
            CImg<unsigned char> img(it.w, it.h, 1, 4);
            for (int i = 0; i < it.w; ++i)
            {
                for (int j = 0; j < it.h; ++j)
                {
                    for (int c = 0; c < 4; ++c)
                    {
                        auto temp = imgSource.atXYZC(x + i, y + j, 1, c);
                        img.atXYZC(i, j, 1, c) = temp;
                    }
                }
            }
            char name[100];
            sprintf(name, "%s%s.png", path.c_str(), it.name.c_str());
            img.save_png(name);
            cout<<"复制文件:"<<name<<endl;
        }
        else
        {
            int width = it.w;
            int height = it.h;
            int x = it.x;
            int y = it.y;
            
            CImg<unsigned char> img(width, height, 1, 4);
            for (int i = 0; i < width; ++i)
            {
                for (int j = 0; j < height; ++j)
                {
                    for (int c = 0; c < 4; ++c)
                    {
                        auto temp = imgSource.atXYZC(x + height - j, y + i, 1, c);
                        img.atXYZC(i, j, 1, c) = temp;
                    }
                }
            }
            char name[100];
            sprintf(name, "%s%s.png", path.c_str(), it.name.c_str());
            img.save_png(name);
            cout<<"复制文件:"<<name<<endl;
        }
    }
    cout<<"结束复制文件"<<endl;
}

vector<frameStruct> CImageHandle::getFrameStruct(const string &file)
{
    vector<frameStruct> reuslt;
    
    fs::path p(file);
    
    fs::ifstream ifile;
    ifile.open(p);
    
    auto getKeyValue = [](string s, string findKey)
    {
        size_t startPos = s.find(findKey) + findKey.size();
        size_t endPos = s.find(",");
        if (endPos == string::npos){
            endPos = s.size();
        }
        string temp = s.substr(startPos, endPos - startPos);
        stringstream ss;
        int result(0);
        ss<<temp;
        ss>>result;
        return result;
    };
    
    int index = 0;
    string s;
    string lastS;
    while (getline(ifile, s))
    {
        if (s.find("\"frame\"") != string::npos)
        {
            //找到开始位置了
            frameStruct frame;
            frame.rotated = false;
            //name
            size_t nameStart = lastS.find("\"") + 1;
            frame.name = lastS.substr(nameStart, lastS.find(".png") - nameStart);
            //x
            getline(ifile, s);
            frame.x = getKeyValue(s, "\"x\": ");
            //y
            getline(ifile, s);
            frame.y = getKeyValue(s, "\"y\": ");
            //w
            getline(ifile, s);
            frame.w = getKeyValue(s, "\"w\": ");
            //h
            getline(ifile, s);
            frame.h = getKeyValue(s, "\"h\": ");
            
            index++;
            reuslt.push_back(frame);
        }
        lastS = s;
    }
    

    return reuslt;
}





















