#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include <string>
using namespace std;

class Animal
{
public:
	Animal();
	~Animal();
	void testTypeId();
	string mName;
	int mAge;
	bool operator > (Animal a);
	bool operator < (Animal a);
	bool operator == (Animal a);
private:
};

#endif