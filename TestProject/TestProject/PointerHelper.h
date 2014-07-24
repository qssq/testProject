#ifndef _POINTER_HELPER_H_
#define _POINTER_HELPER_H_

#include <iostream>
#include <string>
#include <memory>

class ClassA
{
public:
	virtual ~ClassA();
	virtual void display() const;
};

class ClassB : public ClassA
{
public:
	void display() const;
};
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
	void byReferenceTest();
private:
	void displayClassByValue(ClassA c);
	void displayClassByRefernce(const ClassA &c);
};

#endif