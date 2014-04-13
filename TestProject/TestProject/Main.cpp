#include <iostream>
#include <fstream>
#include <string>
#include "EncryptionHelper.h"
#include "FileHelper.h"

using namespace std;

int main(int argc, char *argv[])
{
	FileHelper fh("input.txt");
	fh.file();
	fh.readString();
	system("pause");
	return 0;
}