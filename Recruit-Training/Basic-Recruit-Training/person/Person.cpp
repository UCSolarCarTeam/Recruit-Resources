#include "Person.h"
#include <iostream>

Person::Person()
{
    name_=" ";
    *age;
}

Person::~Person()
{
    std::cout<<"Inside Destructor \n";
}

Person::Person(const std::string& name, int age)
{
    name_=name;
    this->age= new int(age);
}

int Person::getAge() const{
    return *age;
}

const std::string& Person::getName() const
{
    return name_;
}

void Person::setName(const std::string& newName)
{
    name_= newName;
}

void Person::setAge(int newAge)
{
    this->age= new int(newAge);
}

void Person::printInfo() const
{
    std::cout<< "Name is: "<< name_<< "and age is: "<< *age<< "\n";
}

int Person::combinedAge(Person* personArray[], int size)
{
    int sum = 0;
    for(int i = 0; i < size; i++)
    {
        Person *x= personArray[i];
        sum+=(*x).getAge();
    }
    return sum;
}

void Person::birthday(Person& x)
{
    x.setAge(x.getAge()+1);
}