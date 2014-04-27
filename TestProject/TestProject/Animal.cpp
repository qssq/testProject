#include "Animal.h"
#include <iostream>

using namespace std;

Animal::Animal()
{

}

Animal::~Animal()
{

}

bool Animal::operator>( Animal a )
{
	return this->mAge > a.mAge;
}

bool Animal::operator<( Animal a )
{
	return this->mAge < a.mAge;
}

bool Animal::operator==( Animal a )
{
	return this->mAge == a.mAge;
}

void Animal::testTypeId()
{
	Animal a;
	cout<<typeid(a).name()<<endl;

	Animal *a1 = new Animal();
	cout<<typeid(*a1).name()<<endl;
	delete a1;
}
