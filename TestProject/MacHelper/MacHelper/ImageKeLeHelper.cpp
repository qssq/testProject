//
//  ImageKeLeHelper.cpp
//  MacHelper
//
//  Created by gongxun on 17/10/10.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "ImageKeLeHelper.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>
#include "FileHelper.h"
#include "CImageHandle.h"

using namespace boost::property_tree;
using namespace std;

ImageKeLeHelper::ImageKeLeHelper()
{
    
}

ImageKeLeHelper::~ImageKeLeHelper()
{
    
}

void ImageKeLeHelper::start()
{
    FileHelper fileHelper;
    
    string fileName = "/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/pokerCard.json";
    string fileImageName = "/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/pokerCard.png";
    string outPath = "kele/";
    
    ///1分解json 找到key和对应的uuid
    ///2通过uuid找到对应的json文件
    
    //1
    fstream inFile;
    inFile.open(fileName.c_str());
    
    stringstream ss;
    ss<<inFile.rdbuf();
    ptree pt;
    try
    {
        read_json(ss, pt);
    }
    catch (ptree_error & e)
    {
        return;
    }
    
    vector<string> keys;
    vector<string> uuids;
    try
    {
        ptree spriteFrames = pt.get_child("_spriteFrames");
        for (ptree::iterator it = spriteFrames.begin(); it != spriteFrames.end(); ++it)
        {
            string key = it->first;
            string uuid = it->second.get<string>("__uuid__");
            
            keys.push_back(key);
            uuids.push_back(uuid);
        }
        
    }
    catch (ptree_error & e)
    {
        return;
    }
    
    for (int i = 0; i < keys.size(); ++i)
    {
//        cout<<"key:"<<keys[i]<<" uuid:"<<uuids[i]<<endl;
    }
    
    //2
    vector<frameStruct> frameStructs;
    vector<string> allFiles = fileHelper.getDirectoryFile("/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/kele");
    for (int i = 0; i < keys.size(); ++i)
    {
        string uuid = uuids[i];
        string uuidFile = "";
        for (string file : allFiles)
        {
            if (file.find(uuid) != string::npos)
            {
                uuidFile = file;
                break;
            }
        }
        
        cout<<"uuid:"<<uuid<<" uuidFile:"<<uuidFile<<endl;
        
        if (uuidFile != "")
        {
            ptree posJson;
//            fileHelper.getJSONFile(uuidFile, posJson);
            
            fstream inFile;
            inFile.open(uuidFile.c_str());
            
            stringstream ss;
            ss<<inFile.rdbuf();
            try
            {
                read_json(ss, posJson);
            }
            catch (boost::property_tree::ptree_error & e)
            {
                throw "不是json文件";
            }
            
            frameStruct frame;
            frame.name = keys[i];
            
            ptree content = posJson.get_child("content");
            ptree rect = content.get_child("rect");
            ptree::iterator it = rect.begin();
            for (int j = 0; j < 4; j++)
            {
                if (j == 0)
                {
                    frame.x = it->second.get_value<int>();
                }
                else if (j == 1)
                {
                    frame.y = it->second.get_value<int>();
                }
                else if (j == 2)
                {
                    frame.w = it->second.get_value<int>();
                }
                else if (j == 3)
                {
                    frame.h = it->second.get_value<int>();
                }
                ++it;
            }
            
            frame.rotated = true;
            try {
                content.get_child("rotated");
            } catch (ptree_error & e) {
                frame.rotated = false;
            }
            frameStructs.push_back(frame);
        }
    }
    
    //3导出
    CImageHandle imageHelper;
    imageHelper.copyFiles(frameStructs, fileImageName, outPath);
    
    
//    std::string str = "{\"code\":0,\"images\":[{\"url\":\"fmn057/20111221/1130/head_kJoO_05d9000251de125c.jpg\"},{\"url\":\"fmn057/20111221/1130/original_kJoO_05d9000251de125c.jpg\"}]}";
//    
//    std::stringstream ss(str);
//    ptree pt;
//    try{
//        read_json(ss, pt);
//    }
//    catch(ptree_error & e) {
//        return;
//    }
//    
//    try{
//        int code = pt.get<int>("code");   // 得到"code"的value
//        ptree image_array = pt.get_child("images");  // get_child得到数组对象
//        
//        // 遍历数组
//        for(boost::property_tree::ptree::value_type &v : image_array)
//        {
//            std::stringstream s;
//            write_json(s, v.second);
//            std::string image_item = s.str();
//        }
//    }
//    catch (ptree_error & e)
//    {
//        return;
//    }
//    return;
}
