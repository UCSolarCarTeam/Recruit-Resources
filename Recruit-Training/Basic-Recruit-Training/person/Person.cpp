#include "Person.h"

#include <iostream>

Person::Person() : name_(""), age_(new int(0)) {} //Default constructor

Person::Person (const std::string& name, int age) //Constructor
  : name_(name), age_(new int(age)) {}

Person::~Person() //Destructor
{
  delete age_;
}

int Person::getAge() const //Getter for age
{
  return *age_;
}

void Person::setAge(int newAge) //Setter for age
{
  *(age_) = newAge;
}

const std::string& Person::getName() const //Getter for name
{
  return name_;
}

void Person::setName(const std::string& newName) //Setter for name
{
  name_ = newName;
}

void Person::printInfo() const //printInfo function
{
  std::cout << name_ << std::endl;
  std::cout << *(age_) << std::endl;
}

void Person::birthday(Person& x) //birthday function
{
  x.setAge(x.getAge() + 1);
}

int Person::combinedAge(Person** personArray, int size) //combinedAge function
{
  int i;
  int totalAge = 0;

  for(i = 0; i < size; i++)
  {
    totalAge += (*(personArray[i])).getAge();

  }
  return totalAge;
}
