#include "Person.h"
#include <iostream>
#include <string>
#include <sstream>
Person::Person(void)
{
    name_ = "";
    age_ = new int(0);
}

Person::Person(const std::string& name, int age)
{
    name_ = name;
    age_ = new int(age);
}
Person::~Person()
{
    std::cout << "Get dead" << std::endl;
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
    std::cout << "Name:" << name_ << std::endl
              << "Age:"  << *age_ << std::endl;
}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    age_ = new int(newAge);
}

int Person::combinedAge(Person** x, int size)  // Print the combined Age of everyone pointed to by x
{
    int totalAge = 0;
    for(int i = 0; i < size; i++)
    {
        //int a = x[i]->getAge();
        totalAge = x[i]->getAge() + totalAge;
        std::cout << totalAge << std::endl;
    }
    return totalAge;
}
void Person::birthday(Person& x)
{
    int a = x.getAge() + 1;
    x.setAge(a);

}





