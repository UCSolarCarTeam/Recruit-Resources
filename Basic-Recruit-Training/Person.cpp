#include "Person.h"

Person :: Person ()
{

}

Person :: Person(const std::string& name, int age)
{
    name_ = name;
    age_ = new int(age);
}

const std::string& Person :: getName () const
{
    return name_;
}

int Person :: getAge () const
{
    return *age_;
}

void Person :: setAge (int newAge)
{
   delete(age_);
   age_ = new int(newAge);
}

static int Person :: combinedAge(Person** x, int size)
{



}


Person :: ~Person ()
{

}


