//This line is a preprocessor directive that prevents this header file from accidentally being included multiple times by source files.
#pragma once

#include <string>
class Person
{
public:
//A Rule of Thumb when designing classes is to have a default constructor, regular constructor, and a destructor. This is the referred to as the rule of three in C++ programming.
	Person();
	Person(const std::string name, int age);
	~Person();

	int getAge() const;
	std::string getName() const;

	void printInfo();

	void setName(const std::string newName);
	void setAge(int newAge);
	static int combinedAge(Person** personArray);
	static void birthday(Person& x);
private:
	std::string name_;
	int age_;
};


