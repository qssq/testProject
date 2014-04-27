#include "GenericHelper.h"

GenericHelper::GenericHelper()
{

}

GenericHelper::~GenericHelper()
{

}

void GenericHelper::testStdFind()
{
	vector<int> iVector;
	iVector.push_back(1);
	iVector.push_back(12);
	iVector.push_back(8);
	iVector.push_back(7);
	iVector.push_back(7);
	iVector.push_back(123);
	iVector.push_back(127);
	iVector.push_back(72);

	int val = 13;

	vector<int>::iterator result = std::find(iVector.begin(), iVector.end(), val);
	cout<<"values is "<<(result == iVector.cend() ? "no" : "yes")<<endl;

	int count = std::count(iVector.begin(), iVector.end(), 7);
	cout<<"count is "<<count<<endl;

	vector<double> dVector;
	dVector.push_back(0.12);
	dVector.push_back(0.121);
	dVector.push_back(0.13);
	dVector.push_back(0.32);
	dVector.push_back(0.432);

	auto value = std::accumulate(dVector.begin(), dVector.end(), 0.0);
	cout<<value<<endl;
}

void GenericHelper::testInserter()
{
	vector<int> vec;

	fill_n(back_inserter(vec), 5, 8);
	for (int it : vec)
	{
		cout<<it<<endl;
	}
	cout<<"---------"<<endl;

	int a[] ={10, 20, 30};
	int a1[sizeof(a)/sizeof(*a)];
	copy(begin(a), end(a), a1);
	for (int it : a1)
	{
		cout<<it<<endl;
	}
}

void GenericHelper::testFill_n()
{
	vector<int> iVec;
	iVec.push_back(12);
	iVec.push_back(23);
	iVec.push_back(23);
	iVec.push_back(423);

	fill_n(iVec.begin(), iVec.size(), 0);
	for (auto it : iVec)
	{
		cout<<it<<endl;
	}

	//test
	vector<int> vec;
	vec.resize(10);
	fill_n(vec.begin(), 10, 0);

}

//true位置不变， false位置改变
bool GenericHelper::isShorter(const string &s1, const string &s2)
{
	if (s1.size() != s2.size())
	{
		if (s1.size() > s2.size())
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return s1 < s2;
	}
}

void GenericHelper::testSort()
{
	vector<string> vec;
	vec.push_back("fox");
	vec.push_back("jumps");
	vec.push_back("over");
	vec.push_back("quick");
	vec.push_back("red");
	vec.push_back("slow");
	vec.push_back("fox");
	vec.push_back("turtle");
	vec.push_back("over");
	vec.push_back("end");


	sort(vec.begin(), vec.end(), GenericHelper::isShorter);
	for (auto it : vec)
	{
		cout<<it<<endl;
	}
	cout<<"---------------"<<endl;
	auto end_unique = unique(vec.begin(), vec.end());
	for (auto it : vec)
	{
		cout<<it<<endl;
	}
	cout<<"---------------"<<endl;
	vec.erase(end_unique, vec.end());
	for (auto it : vec)
	{
		cout<<it<<endl;
	}
}
