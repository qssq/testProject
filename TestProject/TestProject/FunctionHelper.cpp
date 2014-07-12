#include "FunctionHelper.h"

FunctionHelper::FunctionHelper()
{

}

FunctionHelper::~FunctionHelper()
{

}

int sub(int a, int b)
{
	return a- b;
}

void FunctionHelper::ArithmeticTest()
{
	map<string, function<int(int, int)>> arithmetic;
	function<int(int, int)> f1 =  [](int a, int b){ return a + b;};
	function<int(int, int)> f2 =  sub;
	arithmetic.insert(make_pair("+", f1));
	arithmetic.insert(make_pair("-", f2));
	arithmetic.insert(make_pair("*", [](int a, int b){ return a * b;}));
	arithmetic.insert(make_pair("/", [](int a, int b){ return a / b;}));

	for (auto it : arithmetic)
	{
		cout<<it.second(2, 5)<<endl;
	}
}

void FunctionHelper::ConversionTest()
{
}
