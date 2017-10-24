#include <iostream>

#include "Person.h"

Person::Person()
: Person("No name", 0) {
}

Person::Person(const std::string& name, int age)
: name_(name)
{
	age_ = new int;
	*age_ = age;
}

Person::~Person() {
	delete age_;
}

int Person::getAge() const {
	return *age_;
}

const std::string& Person::getName() const {
	return name_;
}

void Person::printInfo() {
	std::cout << name_ << "'s age is " << *age_ << std::endl;
}

void Person::setName(const std::string& newName) {
	name_ = newName;
}

void Person::setAge(int newAge) {
	*age_ = newAge;
}

int Person::combinedAge(Person** x, int size) {
	int sumAge = 0;
	for(int i = 0; i < size; i++) {
		sumAge += x[i]->getAge();
	}
	return sumAge;
}


void Person::birthday(Person& x) {
	x.setAge(x.getAge() + 1);
}
