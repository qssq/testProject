#ifndef _RANDOM_HELPER_H_
#define _RANDOM_HELPER_H_

#include <iostream>
#include <random>
#include <vector>

using namespace std;

class RandomHelper
{
public:
	RandomHelper();
	~RandomHelper();
	void threeCarTest();
	int getRandomIndex(int vsize,vector<int> Ignores);
	int gettest();
};
#endif