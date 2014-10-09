#include "ArrayHelper.h"

ArrayHelper::ArrayHelper()
{

}

ArrayHelper::~ArrayHelper()
{

}

void ArrayHelper::testVector()
{
	//排序
	vector<int> iVector;
	iVector.push_back(123);
	iVector.push_back(2);
	iVector.push_back(123453);
	iVector.push_back(123);
	iVector.push_back(12);
	iVector.push_back(334545);
	iVector.push_back(5345345);
	iVector.push_back(123);
	iVector.push_back(45);
	iVector.push_back(12);
	iVector.push_back(123);
	iVector.push_back(345);
	iVector.push_back(12);
	for (auto it : iVector)
	{
		cout<<it<<endl;
	}
	cout<<"------------------------------------------------\r\n";
	std::sort(iVector.begin(), iVector.end());
	for (auto it : iVector)
	{
		cout<<it<<endl;
	}
}

void ArrayHelper::testSwap()
{
	//swap
	vector<int> swap1(3, -2);
	vector<int> swap2(5, 12);
	std::swap(swap1, swap2);
	for (auto it : swap1)
	{
		cout<<it<<endl;
	}
	//assign
	cout<<"----------assign----------"<<endl;
	vector<int> seq;
	seq.assign(swap1.begin(), swap1.end());
	for (auto it : seq)
	{
		cout<<it<<endl;
	}
}

void ArrayHelper::testOperators()
{
	vector<Animal> animals;
	Animal Chicken, Duck, Goose, Quail, Sparrow;
	Chicken.mName = "小鸡";
	Chicken.mAge = 5;
	animals.push_back(Chicken);

	Duck.mName = "鸭子";
	Duck.mAge = 6;
	animals.push_back(Duck);

	Goose.mName = "鹅";
	Goose.mAge = 8;
	animals.push_back(Goose);

	Quail.mName = "鹌鹑 ";
	Quail.mAge = 3;
	animals.push_back(Quail);

	Sparrow.mName = "麻雀";
	Sparrow.mAge = 4;
	animals.push_back(Sparrow);

	//关系运算符
	cout<<"---------------关系运算符---------------"<<endl;
	bool b = Chicken > Duck;
	if (b)
	{
		cout<<"正确"<<endl;
	}
	else
	{
		cout<<"错误"<<endl;
	}
	//sort
	cout<<"---------------sort---------------"<<endl;
	std::sort(animals.begin(), animals.end());
	for (auto it : animals)
	{
		cout<<it.mName<<endl;
	}
}

void ArrayHelper::testFind()
{
	string numbers = "0123456789";
	string dept = "a1a8asdf887sdfa9sd88ss8d7s8s";
	string::size_type pos = 0;

	while ((pos = dept.find_first_of(numbers, pos)) != string::npos)
	{
		cout<<"index:"<<pos<<" values = "<<dept[pos]<<endl;
		++pos;
	}

}

void ArrayHelper::testNumericConversion()
{
	int i = 42;
	string s = std::to_string(i);
	cout<<s<<endl;

	double d = std::stod("123.123");
	cout<<d<<endl;

	string s2 = "PI = 3.1415926";
	double d2 = std::stod(s2.substr(s2.find_first_of("+-.0123456789")));
	cout<<d2<<endl;
}

struct testFindAndEarseStruct
{
	int id;
	string name;
};

void ArrayHelper::testFindAndEarse()
{
	testFindAndEarseStruct a = {1, "haha"};
	testFindAndEarseStruct b = {2, "woshi"};
	testFindAndEarseStruct c = {3, "xun"};
	vector<testFindAndEarseStruct> testFindAndEarseStructs;
	testFindAndEarseStructs.push_back(a);
	testFindAndEarseStructs.push_back(b);
	testFindAndEarseStructs.push_back(c);

	testFindAndEarseStruct test = {1, "test"};

	auto it = find_if(testFindAndEarseStructs.begin(), testFindAndEarseStructs.end(), 
		[test](const testFindAndEarseStruct &a)
	{
		return a.id == test.id;
	});

	if (it != testFindAndEarseStructs.end())
	{
		testFindAndEarseStructs.erase(it);
		testFindAndEarseStructs.push_back(test);
	}

	for (auto it : testFindAndEarseStructs)
	{
		cout<<it.name<<endl;
	}
}
