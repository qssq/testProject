
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

using namespace std;

int main(int argc, char *argv[])
{
	PointerHelper ptrHelper;
	ptrHelper.shared_ptrTest();
	system("pause");
	return 0;
}