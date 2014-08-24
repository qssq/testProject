
#include <iostream>
#include <fstream>
#include <string>
#include "vld.h"

#include "EncryptionHelper.h"
#include "FileHelper.h"
#include "ArrayHelper.h"
#include "GenericHelper.h"
#include "AssociativeHelper.h"
#include "FunctionHelper.h"
#include "CreateGenericHelper.h"
#include "RandomHelper.h"
#include "PointerHelper.h"
#include "ThreadHelper.h"
#include "Question.h"
#include "TemplateHelper.h"
#include "dataStructure/DataString.h"

using namespace std;

int main(int argc, char *argv[])
{
	TemplateHelper th;
	string intS = th.toString(109);
	string doubleS = th.toString(121.2121);
	string floatS = th.toString(88.01f);
	cout<<intS<<endl;
	cout<<doubleS<<endl;
	cout<<floatS<<endl;

	string SDouble = "121.2121233";
	string SInt = "888";
	double d1 = th.parseString<double>(SDouble);
	int i1 = th.parseString<int>(SInt);

	system("pause");
	return 0;
}