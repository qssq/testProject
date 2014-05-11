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
	vector<int> ivec;
	int cinInt;
	while (cin>>cinInt)
	{
		auto itS = inserter(ivec, ivec.begin());
		itS = cinInt;
	}
	for (auto it : ivec)
	{
		cout<<it<<endl;
	}

	cout<<"---------"<<endl;
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

void GenericHelper::testIoInserter()
{
	vector<int> vec;
	istream_iterator<int> in_iter(cin);
	istream_iterator<int> eof;
	while (in_iter != eof)
	{
		vec.push_back(*in_iter++);
	}
	cout<<"-------------------"<<endl;
	for (auto it : vec)
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

void GenericHelper::testLambda()
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
	for (auto it : vec)
	{
		cout<<it<<endl;
	}

	stable_sort(vec.begin(), vec.end(), 
	[](const string &a, const string &b)
	{
		return a.size() < b.size();
	});

	cout<<"--------------------------------"<<endl;
	for (auto it : vec)
	{
		cout<<it<<endl;
	}

	cout<<"--------------------------------"<<endl;
	vector<int> cards;
	cards.push_back(10);
	cards.push_back(7);
	cards.push_back(2);
	cards.push_back(12);
	cards.push_back(32);
	cards.push_back(22);
	cards.push_back(90);

	int card = 12;
	auto it = find_if(cards.begin(), cards.end(), 
		[card](const int &a)
	{
		return a == card;
	});
	cout<<*it<<endl;

	cout<<"--------------------------------"<<endl;
	for_each(cards.begin(), cards.end(), [](const int &a){cout<<a<<endl;});
}

void GenericHelper::testLambda1()
{
	int v1 = 42;
	auto f = [v1](){return v1;};
	v1 = 32;
	cout<<f()<<endl;
}

void GenericHelper::testRandom()
{
	//random_device rd;
	//for (int i = 0; i < 100; i++)
	//{
	//	cout<<rd()%10<<endl;
	//}

	//std::default_random_engine generator;  
	//std::uniform_int_distribution<int> dis(0,10);  
	//for(int i=0;i<10;i++)  
	//{  
	//	std::cout<<dis(generator)<<std::endl;  
	//}  

	std::default_random_engine generator(time(NULL));  
	std::uniform_int_distribution<int> dis(0,2);  
	auto dice= std::bind(dis,generator);  
	for(int i=0;i<10;i++)  
	{  
		std::cout<<dice()<<std::endl;  
	}  
}

void GenericHelper::testritertor()
{
	vector<int> ivec;
	ivec.push_back(1);
	ivec.push_back(2);
	ivec.push_back(3);
	ivec.push_back(4);
	ivec.push_back(5);
	ivec.push_back(6);

	for (auto it = ivec.rbegin(); it != ivec.rend(); ++it)
	{
		cout<<*it<<endl;
	}
	cout<<"----------升序----------"<<endl;
	sort(ivec.begin(), ivec.end());
	for (auto it : ivec)
	{
		cout<<it<<endl;
	}
	cout<<"----------降序----------"<<endl;
	sort(ivec.rbegin(), ivec.rend());
	for (auto it : ivec)
	{
		cout<<it<<endl;
	}
	cout<<"----------反向查找----------"<<endl;
	string s = "12222222222212";
	auto rcomma = find(s.rbegin(), s.rend(), '1');
	cout<<string(s.rbegin(), rcomma)<<endl;
}

void GenericHelper::testCppy()
{
	vector<int> number;
	int i = 0;
	while (i < 10)
	{
		number.push_back(++i);
	}
	vector<int> jishu;

	copy_if(number.begin(), number.end(), back_inserter(jishu), [](int a)
	{
		return (a%2 == 1);
	});

	for (auto it : jishu)
	{
		cout<<it<<endl;
	}
}
