//This line is a preprocessor directive that prevents this header file from accidentally being included multiple times by source files.
#pragma once

#include <string>
class Person
{
public:
//A Rule of Thumb when designing classes is to have a default constructor, regular constructor, and a destructor.
	Person();
	Person(const std::string name, int age);
	~Person();

	int getAge() const;
	std::string getName() const;

	void printInfo();

	void setName(const std::string newName);
	void setAge(int newAge);
//Print the combined Age of everyone pointed to by x
	static int combinedAge(Person** x, int size);
	static void birthday(Person& x);
private:
	std::string name_;
//age_ should be a dynamically allocated.
	int* age_;

};


