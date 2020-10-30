#include "Person.h"
#include <iostream>

Person::Person(){
	age_ = new int[0];
};

Person::~Person(){
	delete age_;
}

Person::Person(const std::string& name, int age) {
	name_ = name;
	age_ = new int[1];
	age_[0] = age;
}

int Person::getAge() const {
	return age_[0];
}

const std::string& Person::getName() const {
	return name_;
}

void Person::setName(const std::string& newName) {
	name_ = newName;
}

void Person::setAge(int newAge) {
	age_[0] = newAge;
}

void Person::printInfo() const {
	printf("Name: %s\nAge: %d\n", name_.c_str(), age_[0]);
}

int Person::combinedAge(Person** personArray, int size){
	int sum = 0;
	for(int i = 0; i < size; i++)
		sum += personArray[i]->age_[0];
	return sum;
}

void Person::birthday(Person& x){
	x.setAge(x.getAge() + 1);
}