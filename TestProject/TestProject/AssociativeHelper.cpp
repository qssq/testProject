#include "AssociativeHelper.h"

AssociativeHelper::AssociativeHelper()
{

}

AssociativeHelper::~AssociativeHelper()
{

}

bool LenghtCompare1( const string &a, const string &b )
{
	return a.size() > b.size();
}

void AssociativeHelper::FuncPointerTest()
{
	PF pf1 = (PF)(&AssociativeHelper::LenghtCompare);
	bool dayu = (this->*pf1)("aaaaa", "bbbb");
	cout<<dayu<<endl;
}

bool AssociativeHelper::LenghtCompare( const string &a, const string &b )
{
	return a.size() > b.size();
}

void AssociativeHelper::mapTest()
{
	map<string, size_t> word_cout;
	set<string> exclude;
	exclude.insert(exclude.end(), "the");
	exclude.insert(exclude.end(), "but");
	exclude.insert(exclude.end(), "and");
	exclude.insert(exclude.end(), "or");

	string word;
	while (cin>>word)
	{
		if (exclude.find(word) == exclude.end())
		{
			++word_cout[word];
		}
	}
	for (auto it : word_cout)
	{
		cout<<"keys = "<<it.first<<"  values = "<<it.second<<endl;
	}
}

void AssociativeHelper::multisetTest()
{
	map<int, string> map1;
	pair<int ,string> pair1(1, "One");
	map1.insert(pair1);
	for (auto it : map1)
	{
		cout<<it.second<<endl;
	}
}
