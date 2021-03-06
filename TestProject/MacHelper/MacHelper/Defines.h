//
//  Defines.h
//  MacHelper
//
//  Created by gongxun on 17/5/11.
//  Copyright © 2017年 gongxun. All rights reserved.
//

#ifndef Defines_h
#define Defines_h

#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include <chrono>

using namespace std;

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

//int
inline int getIntForString(const string &s)
{
    stringstream ss;
    int result(0);
    ss<<s;
    ss>>result;
    return result;
}

//c++ 11 toString
template <typename T>
string getString(T value)
{
    ostringstream oss;
    string s;
    oss<<value;
    s = oss.str();
    return s;
}

//返回格式化时间
inline string getCurDateTime()
{
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto time = std::put_time(std::localtime(&t), "%Y-%m-%d %X");
    ostringstream oss;
    oss<<time;
    string s = oss.str();
    return s;
}


#endif /* Defines_h */
