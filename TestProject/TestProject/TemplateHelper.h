#ifndef _TEMPLATE_HELPER_H_
#define _TEMPLATE_HELPER_H_

#include <string>

class TemplateHelper
{
public:
	TemplateHelper();
	~TemplateHelper();
	template <typename T>
	std::string toString(const T &v)
	{
		stringstream ss;
		string s;
		ss<<v;
		ss>>s;
		return s;
	}
	template <typename T>
	T parseString(const string &v)
	{
		stringstream ss;
		ss.str(v);
		T result;
		ss>>result;
		return result;
	}
private:

};

#endif