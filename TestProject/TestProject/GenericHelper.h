#ifndef _GENERIC_HELPER_H_
#define _GENERIC_HELPER_H_

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <numeric>
#include <random>
#include <time.h>
#include <functional>

using namespace std;

class GenericHelper
{
public:
	GenericHelper();
	~GenericHelper();
	void testStdFind();		//÷ª∂¡À„∑®
	void testInserter();	//–¥»›∆˜À„∑®
	void testIoInserter();
	void testFill_n();
	void testSort();
	void testLambda();
	void testLambda1();
	void testRandom();
	void testritertor();

	static bool isShorter(const string &s1, const string &s2);
private:

};
#endif