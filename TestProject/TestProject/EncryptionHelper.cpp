#include "EncryptionHelper.h"

const string mKey = "woshidashabi";

EncryptionHelper::EncryptionHelper()
{

}

EncryptionHelper::~EncryptionHelper()
{

}

std::string EncryptionHelper::codeData( string data )
{
	int keylenght = mKey.length();
	int datalenght = data.length();
	for (int i=0; i< datalenght; i++)
	{
		data[i]^= mKey[(i) % keylenght];
	}
	return data;
}
