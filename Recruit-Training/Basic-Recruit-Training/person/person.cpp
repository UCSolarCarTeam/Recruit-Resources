#include"Person.h"
#include<iostream>
#include<string>
Person::Person()
{
    name_ = " ";
    age_ = new int;
}
Person::Person(const std::string& name, int age)
{
    name_ = name;
    age_ = new int;
    *age_ = age;
}
Person::~Person()
{
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
int Person::getAge()const
{
    return *age_;
}
const std::string & Person::getName() const
{
    return name_;
}
void Person::printInfo() const
{
    std::cout << name_ << " " << *age_;
}
    
int Person::combinedAge(Person** personArray, int size)
{
    int sum = 0;
    for(int i = 0;i < size;i++)
    { 
        
        sum += personArray[i]->getAge();
        
    }
    
    return sum;
}  

    
void Person::birthday(Person& x)
{
    int tempAge = x.getAge();
    tempAge += 1;
    x.setAge(tempAge);
}   

