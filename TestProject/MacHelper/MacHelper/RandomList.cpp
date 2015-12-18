//
//  RandomList.cpp
//  MacHelper
//
//  Created by gongxun on 15/12/18.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#include "RandomList.h"
#include <fstream>

RandomList::RandomList()
{
    
}

RandomList::~RandomList()
{
    
}

vector<int> mList;
vector<bool> mFullList;
const int zongjin = 1000;

int randomNum(int num1, int num2)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(num1, num2);
    return dis(gen);
}

void setListValue(int index, int value)
{
    mFullList[index] = true;
    mList[index] = value;
}

void setListZero(int index)
{
    if (mFullList[index])
    {
        setListZero(randomNum(0, 9));
    }
    else
    {
        setListValue(index, 0);
    }
}

void setListFrist()
{
    int index = randomNum(0, 9);
    if (!mFullList[index])
    {
        setListFrist();
    }
    else
    {
        setListValue(index, randomNum(0, zongjin / 10));
    }
}

//返回是否 用完
bool getListIndex(int &outindex)
{
    bool isEnd = true;
    vector<int> useList;
    
    for (int i = 0; i < mFullList.size(); ++i)
    {
        if (!mFullList[i])
        {
            isEnd = false;
            useList.push_back(i);
        }
    }
    
    if (!isEnd)
    {
        outindex = useList[randomNum(0, useList.size() - 1)];
    }
    
    return isEnd;
}

int getMax(const vector<int> &list)
{
    int max = 0;
    for (auto it : list)
    {
        if (it > max)
        {
            max = it;
        }
    }
    
    return max;
}

int getTotal(const vector<int> &list)
{
    int total = 0;
    for (auto it : list)
    {
        total += it;
    }
    return total;
}

int getListMaxValue(vector<int> list)
{
    int maxValue;
    maxValue = (zongjin + getTotal(list)) / 8;
    return maxValue;
}

void setValue(int index)
{
    vector<int> temp = mList;
    int value = randomNum(0, getListMaxValue(temp) - 1);
    temp[index] = value;
    int max = getMax(temp);
    int total = getTotal(temp);
    if (max * 9 - total < zongjin)
    {
        setListValue(index, value);
    }
    else
    {
        setValue(index);
    }
}

int getOnceOffset(vector<int> list, int &out)
{
    out = randomNum(0, 9);
    
    return getTotal(list) - list[out] * 9;
}

void RandomList::start()
{
    cout<<"开始"<<endl;
    

    for (int i = 0; i < 24 * 30 * 3; i++)
    {
        vector<int> list1(10, 0);
        mList = list1;
        vector<bool> list2(10, false);
        mFullList = list2;
        
        //1
        int zeroCount = randomNum(1, 4);
        for (auto i = 0; i < zeroCount; i++)
        {
            setListZero(randomNum(0, 9));
        }
        setListFrist();
        zeroCount++;
        
        
        //2
        int outindex(0);
        for (int i = 0; i < 9 - zeroCount; i++)
        {
            if (!getListIndex(outindex))
            {
                setValue(outindex);
            }
        }
//        for (auto i = 0; i < mList.size(); i++)
//        {
//            cout<<i<<":"<<mList[i]<<endl;
//        }
//        cout<<"end2"<<endl;
        mSaveList.push_back(mList);
    }
    
    showYinli();
}

void RandomList::showYinli()
{
    ofstream ofile;
    ofile.open("tongji.txts");
    
    for (int i = 0; i < mSaveList.size(); i++)
    {
        vector<int> once = mSaveList[i];
        int kaideindex(0);
        mYinli.push_back(getOnceOffset(once, kaideindex));
        mKaiIndex.push_back(kaideindex);
    }
    
    long long zongyingli(0);
    long long onceyingli(0);
    long long maxValue = 0;
    int maxIndex = 0;
    for (int i = 0; i < mYinli.size(); i++)
    {
        if (mYinli[i] < maxValue)
        {
            maxValue = mYinli[i];
            maxIndex = i;
        }
        
//        cout<<"盈利:"<<mYinli[i]<<endl;
        zongyingli += mYinli[i];
        onceyingli += mYinli[i];
        if (i % (23) == 0)
        {
            cout<<"一天的盈利:"<<onceyingli<<endl;
//            cout<<"盈利:"<<onceyingli<<endl;
            onceyingli = 0;
        }
    }
    
    cout<<"亏的最多的一天 开的是:"<<mKaiIndex[maxIndex]<<endl;
    vector<int> kuimax = mSaveList[maxIndex];
    for (auto it : kuimax)
    {
        cout<<it<<endl;
    }
    
    
    cout<<"盈利:"<<zongyingli<<endl;
    
    ofile.close();
}












