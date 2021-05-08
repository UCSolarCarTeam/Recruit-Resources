#include <iostream>
#include <string>
#include "Person.h"

Person::Person() {
	std::string name_ = "";
    int* age_;
}

Person::Person(const std::string& name, int age){
	name_ = name;
	*age_ = age;
}

Person::~Person() { 
	delete age_;
}

int Person::getAge() const{
	return *age_;
}

const std::string& Person::getName() const{
	return name_;
}

void Person::setName(const std::string& newName){
	name_ = newName;
}

void Person::setAge(int newAge){
	*age_ = newAge;
}

void Person::printInfo () const{
	std::cout<< "Name: " << name_;
	std::cout<< "\nAge: " << *age_;
	
}

int Person::combinedAge(Person** personArray, int size){
	int combinedAge = 0;
	for (int i = 0; i < size; i++){
		combinedAge += *personArray[i]->age_;
	}
	return combinedAge;
}

void Person::birthday(Person& x){
	x.age_ += 1;
}





