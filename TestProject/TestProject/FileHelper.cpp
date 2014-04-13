#include "FileHelper.h"

FileHelper::FileHelper()
{

}

FileHelper::FileHelper( string fileName )
{
	mFileName = fileName;
}

FileHelper::~FileHelper()
{

}

void FileHelper::file()
{
	ifstream input(mFileName, ios::binary);
	ofstream output;
	output.open("C:\\Users\\gx\\Desktop\\" + mFileName + ".copy", ios::binary | ios::app);
	if (output)
	{
		string temp;
		while (std::getline(input, temp))
		{
			output<<temp<<endl;
		}
	}
}

struct PersonInfo
{
	string name;
	vector<int> phones;
};

void FileHelper::readString()
{
	string word = "gongxun 123123123123 12325345323";
	stringstream ss(word);
	PersonInfo gongxun;
	ss>>gongxun.name;
	int a;
	while (ss>>a)
	{
		gongxun.phones.push_back(a);
	}
	
}
