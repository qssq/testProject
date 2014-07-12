#include "PointerHelper.h"
using namespace std;

PointerHelper::PointerHelper()
{

}

PointerHelper::~PointerHelper()
{

}

void PointerHelper::shared_ptrTest()
{
	shared_ptr<TestPointer> testPtr1(new TestPointer("test1"));
	shared_ptr<TestPointer> testPtr2(testPtr1);

	testPtr1 = testPtr2;

	cout<<testPtr1->getName()<<endl;

	string s;
	cin>>s;
}




TestPointer::TestPointer( string name ) : mName(name)
{
	cout<<name<<" TestPointer Create"<<endl;
}

TestPointer::~TestPointer()
{
	cout<<mName<<" TestPointer remove"<<endl;
}

TestPointer * TestPointer::getTestPointer()
{
	return new TestPointer("auto");
}

std::string TestPointer::getName()
{
	return mName;
}
