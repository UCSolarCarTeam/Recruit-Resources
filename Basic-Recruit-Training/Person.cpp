#include <iostream>
#include <string>
#include "Person.h"

Person::Person(void)
{
    name_ = "";
    age_ = new int(0);
}

Person::Person(const std::string& name, int age)
:name_(name)
{
    age_ = new int(age);
}

Person::~Person()
{
    delete age_;
}

int Person::getAge(void) const
{
    return *age_;
}

const std::string& Person::getName(void) const
{
    return name_;
}

void Person::printInfo(void)
{
    std::cout << "Name:" << getName() << std::endl
              << "Age:"  << getAge() << std::endl;
}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    *age_ = newAge;
}

int Person::combinedAge(Person** x, int size)
{
    int totalAge = 0;

    for(int i = 0; i < size; i++)
    {
        totalAge = x[i]->getAge() + totalAge;
    }
    return totalAge;
}

void Person::birthday(Person& x)
{
    int birthdayIncrement = x.getAge() + 1;
    x.setAge(birthdayIncrement);
}
