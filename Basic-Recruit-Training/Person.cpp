#include <iostream>
#include "Person.h"

Person::Person()
{
    name_ = "";
    age_ = new int(0);
}

Person::Person(const std::string& name, int a)
{
    name_ = name;
    age_ = new int(a);
}

Person::~Person()
{
    delete age_;
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
    std::cout << "Name: " << getName() << std::endl
              << "Age: " << getAge() << std::endl;

}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    age_ = new int(newAge);
}

void Person::birthday(Person& x)
{
    x.setAge (x.getAge() + 1);
}

int Person::combinedAge(Person** x, int size)
{
    int c = 0;
    for (int index = 0; index < size; index++)
    {
        c = c + (x[index])->getAge();
        std::cout << "combinedAge: " << c << " age:" << (x[index])->getAge() << "\n";
    }

    return c;
}


