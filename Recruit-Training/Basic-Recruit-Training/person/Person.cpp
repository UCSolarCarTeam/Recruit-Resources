#include "Person.h"
#include <iostream>

Person::Person()
{
  name_ = "";
  age_ = new int; //dynamically allocate memory for age_
}

Person::Person(const std::string& name, int age)
{
  name_ = name;
  age_ = new int(age); //dynamically allocate memory for age_
}


Person::~Person()
{
  //de-allocate memory assigned to age
  delete(age_);
}

int Person::getAge() const
{
  return *age_;
}

const std::string& Person::getName() const
{
  return name_;
}

void Person::setName(const std::string& newName)
{
  name_ = newName;
}

void Person::setAge(int newAge)
{
  *age_ = newAge;
}

void Person::printInfo() const
{
  std::cout << "Name: " << name_ << std::endl;
  std::cout << "Age: " << *age_ << std::endl;
}

 int Person::combinedAge(Person** personArray, int size)
{
   int theAge = 0;
   for(int i = 0; i < size; i++)
   {
    theAge = theAge + personArray[i]->getAge(); // same as theAge + (*personArray[i]).getAge() ;
   }
   return theAge;
}

 void Person::birthday(Person& x)
{
  x.setAge(x.getAge() + 1);
}
