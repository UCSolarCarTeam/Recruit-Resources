#include "Person.h"

#include <string>
#include <iostream>

using namespace std;

//default constructor
Person::Person()
: name_("Clare")
{
  age_ = new int(22);
}

//constructor
Person::Person(const string& name, int age)
: name_(name)
{
  age_ = new int(age);
}

//deconstructor
Person::~Person()
{
}

//getters
int Person::getAge() const
{
  return *age_;
}

const string& Person::getName() const
{
  return name_;
}

//setters
void Person::setName(const string& newName)
{
  name_ = newName;
}

void Person::setAge(int newAge)
{
  age_ = new int(newAge);
}

void Person::printInfo() const
{
  cout << "The Person's name is: " << name_ << endl;
  cout << "The Person's age is: " << *age_ << endl;
}

int Person::combinedAge(Person** personArray, int size)
{
  int totalAge = 0;
  for(int i = 0; i < size; i++)
  {
    totalAge = totalAge + personArray[i]->getAge();
  }
  return totalAge;
}

void Person::birthday(Person& x)
{
  int newAge = x.getAge();
  newAge += 1;
  x.setAge(newAge);
}
