#include <iostream>
#include "EncryptionHelper.h"

using namespace std;

int main()
{
	EncryptionHelper eh;
	string last = "gongxun";
	string fast = eh.codeData(last);
	string fast2 = eh.codeData(fast);

	cout<<last<<endl;
	cout<<fast<<endl;
	cout<<fast2<<endl;

	string a = "a";
	a[0] ^= 10;
	cout<<a<<endl;
	a[0] ^= 10;
	cout<<a<<endl;

	system("pause");
	return 0;
}