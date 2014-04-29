#include <iostream>
#include <fstream>
#include <string>
#include "EncryptionHelper.h"
#include "FileHelper.h"
#include "ArrayHelper.h"
#include "GenericHelper.h"

using namespace std;

int main(int argc, char *argv[])
{
	GenericHelper gh;
	gh.testRandom();
	system("pause");
	return 0;
}