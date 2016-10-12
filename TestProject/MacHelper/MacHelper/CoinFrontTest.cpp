//
//  CoinFrontTest.cpp
//  MacHelper
//
//  Created by gongxun on 16/10/8.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "CoinFrontTest.h"


CoinFrontTest::CoinFrontTest()
: mTestCount(10000)
{
    
}

CoinFrontTest::~CoinFrontTest()
{
    
}

void CoinFrontTest::showResult()
{
    long long temp = 0;
    mRandomCount.assign(mTestCount, 0);
    for (int i = 0; i < mTestCount; ++i)
    {
        mRandomCount[i] = getRandomCount();
        printf("攻击次数%d\r\n", mRandomCount[i]);
        temp += mRandomCount[i];
    }
    
    printf("期望值是%0.2f\r\n", temp / (float)mTestCount);
}

int CoinFrontTest::randomNum(int num1, int num2)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(num1, num2);
    return dis(gen);
}

int CoinFrontTest::getRandomCount()
{
    int result = 1;
    while (getFront())
    {
        ++result;
    }
    return result;
}

bool CoinFrontTest::getFront()
{
    return randomNum(1, 100) <= 50;
}












