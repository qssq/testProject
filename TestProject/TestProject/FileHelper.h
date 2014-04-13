#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class FileHelper
{
public:
	FileHelper();
	FileHelper(string fileName);
	~FileHelper();
	void file();
	void readString();
private:
	string mFileName;
};

#endif