#include "Person.h"
#include <iostream>

using namespace::std;

Person::Person(): age_(new int){}

Person::~Person()
{
    delete age_;
}

Person::Person(const std::string& name, int age): name_(name), age_(new int(age)){}

int Person::getAge() const
{
    return *age_;
}

const std::string& Person::getName() const
{
    return name_;
}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    *age_ = newAge;
}

void Person::printInfo() const 
{
	cout << "Name: " << name_ << endl;
	cout << "Age: " << *age_ << endl;
}

int Person::combinedAge(Person** personArray, int size)
{
	int result = 0;

	for(int i = 0; i < size; i++)
    {
		result += *(personArray[i]->age_);
    }

	return result;
}

void Person::birthday(Person& x)
{
    (*x.age_)++;
}

