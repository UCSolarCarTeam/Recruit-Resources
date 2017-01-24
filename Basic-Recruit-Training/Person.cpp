#include "Person.h"

Person :: Person ()
{

}

Person :: Person(const std::string& name, int age)
{
    name_ = name;
    age_ = new int(age);
}

void Person :: setName (const std::string& newName)
{
    name_ = newName;
}

const std::string& Person :: getName () const
{
    return name_;
}


int Person :: getAge () const
{
    return *age_;
}

void Person :: printInfo ()
{
    std :: cout << "The Person's Name is:" << getName() << std :: endl;
    std :: cout << "The Person's Age is :" << getAge() << std :: endl;
}

void Person :: setAge (int newAge)
{
   delete(age_);
   age_ = new int(newAge);
}

int Person :: combinedAge(Person** x, int size)
{
   int ageCombined = 0;
   for (int counter = 0; counter < size; counter++ )
   {
      ageCombined = ageCombined + (x[counter])->getAge();
   }
   return ageCombined;
}

void Person :: birthday(Person& x)
{
    x.setAge (x.getAge() + 1);
}

Person :: ~Person ()
{
    delete(age_);
}


