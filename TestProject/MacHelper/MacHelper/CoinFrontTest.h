//
//  CoinFrontTest.hpp
//  MacHelper
//
//  Created by gongxun on 16/10/8.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#ifndef CoinFrontTest_hpp
#define CoinFrontTest_hpp

#include <string>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class CoinFrontTest
{
public:
    CoinFrontTest();
    ~CoinFrontTest();
    
    void showResult();
    
private:
    int mTestCount;
    vector<int> mRandomCount;
    
    int randomNum(int num1, int num2);
    int getRandomCount();
    bool getFront();
};

#endif /* CoinFrontTest_hpp */
