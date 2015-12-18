//
//  RandomList.hpp
//  MacHelper
//
//  Created by gongxun on 15/12/18.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#ifndef RandomList_hpp
#define RandomList_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <random>

using namespace std;

class RandomList
{
public:
    RandomList();
    ~RandomList();
    void start();
    
private:
    vector<vector<int>> mSaveList;
    vector<long long> mYinli;
    vector<int> mKaiIndex;
    
    void showYinli();
};

#endif /* RandomList_hpp */
