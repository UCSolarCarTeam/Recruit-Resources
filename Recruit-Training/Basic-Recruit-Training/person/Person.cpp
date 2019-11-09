#include "Person.h"

using namespace std;

Person::Person()
{
}

Person::~Person()
{
    delete age_;
}

Person::Person(const std::string& name, int age)
{
    name_ =  name;
    *age_ = age;
}

// setters and getters
int Person::getAge() const
{
    return *age_;
}

const std::string& Person::getName() const
{
    return this->name_;
}

void Person::setName(const std::string& newName)
{
    name_ = newName;
}

void Person::setAge(int newAge)
{
    age_[0] = newAge;
}

// Print out the name and age of the person
void Person::printInfo() const
{
    std::cout << "Name: " << name_ << "\nAge: " << age_ << std::endl;
}

// Print the combined age of everyone pointed to by personArray
int Person::combinedAge(Person** personArray, int size)
{
    int total = 0;
    for(int i = 0; i < size; i ++)
    {
        total += personArray[i]->getAge();
    }
    return total;

}

// Increases the Person's Age by 1
void Person::birthday(Person& x)
{
    x.age_[0] ++;
}
