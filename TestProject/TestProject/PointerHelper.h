#ifndef _POINTER_HELPER_H_
#define _POINTER_HELPER_H_

#include <iostream>
#include <string>
#include <memory>

class TestPointer
{
public:
	TestPointer();
	TestPointer(std::string name);
	~TestPointer();
	std::string getName();
	static TestPointer *getTestPointer();
private:
	std::string mName;
};

class PointerHelper
{
public:
	PointerHelper();
	~PointerHelper();
	void shared_ptrTest();
};

#endif