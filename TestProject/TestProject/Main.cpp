#include <iostream>
#include <fstream>
#include <string>
#include "EncryptionHelper.h"
#include "FileHelper.h"
#include "ArrayHelper.h"
#include "GenericHelper.h"
#include "AssociativeHelper.h"

using namespace std;

int main(int argc, char *argv[])
{
	AssociativeHelper ah;
	ah.multisetTest();
	system("pause");
	return 0;
}