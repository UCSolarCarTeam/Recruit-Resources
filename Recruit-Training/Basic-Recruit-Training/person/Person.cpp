#include "Person.h"
#include "iostream"

Person::Person()
{
    name_ = "";
    age_ = new int;
    *age_ = -1;
}

Person::Person(const std::string& name, int age)
{
    name_ = name;
    age_ = new int;
    *age_ = age;
}

Person::~Person()
{
    name_.clear();
    delete age_;
}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    *age_ = newAge;
}

int Person::getAge() const
{
    return *age_;
}

const std::string& Person::getName() const
{
    return name_;
}

void Person::printInfo() const
{
    std::cout << "Their name is " << name_ << " and their age is " << *age_ << std::endl;
}

int Person::combinedAge(Person** personArray, int size)
{
    int combinedAge = 0;
    for(int i = 0; i < size; i++)
        combinedAge += *personArray[i]->age_;
    return combinedAge;
}

void Person::birthday(Person& x)
{
    x.setAge(x.getAge() + 1);
}
