#include "Person.h"

#include <iostream>

Person::Person()
{
  this -> name_ = "";
  this -> age_ = new int(0);
}

Person::Person (const std::string& name, int age)
{
  this -> name_ = name;
  this -> age_ = new int(age);
}

Person::~Person()
{
  delete age_;
}

int Person::getAge() const
{
  return *age_;
}

void Person::setAge(int newAge)
{
  *(this -> age_) = newAge;
}

const std::string& Person::getName() const
{
  return name_;
}

void Person::setName(const std::string& newName)
{
  this -> name_ = newName;
}

void Person::printInfo() const
{
  std::cout << this -> name_ << std::endl;
  std::cout << *(this -> age_) << std::endl;
}

void Person::birthday(Person& x)
{
  x.setAge(x.getAge() + 1);
}

int Person::combinedAge(Person** personArray, int size)
{
  int i;
  int totalAge = 0;

  for(i = 0; i < size; i++)
  {
    totalAge += (*(personArray[i])).getAge();

  }
  return totalAge;
}
