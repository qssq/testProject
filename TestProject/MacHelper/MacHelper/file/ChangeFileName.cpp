//
//  ChangeFileName.cpp
//  MacHelper
//
//  Created by gongxun on 17/6/5.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#include "ChangeFileName.h"
#include "Defines.h"

ChangeFileName::ChangeFileName()
{
    
}

ChangeFileName::~ChangeFileName()
{
    
}

void ChangeFileName::start(const string &path)
{
    vector<string> oldNames = {
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "10",
        "11",
        "12",
        "13",
        "14",
        "15",
        "16",
        "17",
        "18",
        "19",
        "20",
        "21"
    };
    
    vector<string> newNames = {
        "card_41",
        "card_42",
        "card_43",
        "card_44",
        "card_45",
        "card_46",
        "card_47",
        "card_48",
        "card_49",
        "card_21",
        "card_22",
        "card_23",
        "card_24",
        "card_25",
        "card_26",
        "card_27",
        "card_28",
        "card_29",
        "card_85",
        "card_86",
        "card_87"
    };
    
    //peng hu
    oldNames.push_back("22");
    newNames.push_back("open_peng");
    
    oldNames.push_back("23");
    newNames.push_back("open_liang");
    
    oldNames.push_back("24");
    newNames.push_back("open_gang");
    
    oldNames.push_back("28");
    newNames.push_back("open_hu");
    
    //wintype
    
    oldNames.push_back("26");
    newNames.push_back("hu_winType65536");
    
    oldNames.push_back("27");
    newNames.push_back("hu_winType1024");
    
    oldNames.push_back("29");
    newNames.push_back("hu_winType256");
    
    oldNames.push_back("30");
    newNames.push_back("hu_winType512");
    
    oldNames.push_back("31");
    newNames.push_back("hu_winType2");
    
    oldNames.push_back("32");
    newNames.push_back("hu_winType4");
    
    oldNames.push_back("33");
    newNames.push_back("hu_winType64");
    
    oldNames.push_back("34");
    newNames.push_back("hu_winType128");
    
    oldNames.push_back("35");
    newNames.push_back("hu_winType8");
    
    oldNames.push_back("37");
    newNames.push_back("hu_winType16");
    
    oldNames.push_back("38");
    newNames.push_back("hu_winType8192");
    
    //语音
    for (int i = 0; i < 13; i++)
    {
        oldNames.push_back(getString(i + 101));
        newNames.push_back("chat_" + getString(i));
    }
    
    if (oldNames.size() != newNames.size())
    {
        cout<<"错误 文件不一致"<<endl;
    }
    
    
    vector<string> files = mFileHelper.getDirectoryFile(path);
    for (auto it : files)
    {
        string fileName = mFileHelper.getFileName(it);
        
        for (int i = 0; i < oldNames.size(); ++i){
            string oldName = oldNames[i] + ".mp3";
            if (oldName == fileName)
            {
                string fromFile = path + fileName;
                string toFile = "output/" + newNames[i] + ".mp3";
                
                //复制文件
                mFileHelper.copyFile(fromFile, toFile);
                break;
            }
        }
    }
}
















