#include "CreateGenericHelper.h"

CreateGenericHelper::CreateGenericHelper()
{

}

CreateGenericHelper::~CreateGenericHelper()
{

}

template<typename T>
int compare(const T &v1, const T &v2)
{
	if (v1 > v2) return 1;
	else if (v1 == v2) return 0;
	else return -1;
}

void CreateGenericHelper::CompareTest()
{
	float a1 = 10.21f, b1 = 20.21f;
	int a2 = 2, b2 = 1;
	string a3 = "abc", b3 = "abc";

	cout<<compare<float>(a1, b1)<<endl;
	cout<<compare<int>(a2, b2)<<endl;
	cout<<compare<string>(a3, b3)<<endl;
}
