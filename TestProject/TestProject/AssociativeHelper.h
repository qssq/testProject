#ifndef _ASSOCIATIVE_HELPER_H_
#define _ASSOCIATIVE_HELPER_H_

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <utility>

using namespace std;


class AssociativeHelper
{
public:
	AssociativeHelper();
	~AssociativeHelper();
	void mapTest();
	void multisetTest();
	void FuncPointerTest();

	bool LenghtCompare(const string &a, const string &b);
private:
};

typedef bool (AssociativeHelper::*PF)(const string &a, const string &b);

#endif