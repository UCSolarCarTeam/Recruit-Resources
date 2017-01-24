#include "Person.h"
#include <iostream>
#include <string>

Person::Person()
{
    age_ = new int(0);
    name_="";
}

Person::Person(const std::string& name, int age)
{
    age_ = new int(age);
    name_ = name;
}

Person::~Person()
{
    delete age_;
}

int Person::getAge()const
{
    return *age_;
}

void Person::printInfo()
{
    std::cout << getName() << std::endl;
    std::cout << getAge() << std::endl;
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
    int value = 0;
    for (int i = 0; i<size; i++){
        value += x[i]->getAge();
    }
    std::cout << value;
    return value;
}

void Person::birthday(Person& x)
{
    x.setAge(x.getAge()+1);
}
