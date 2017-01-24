// This line is a preprocessor directive that this header is only defined once.
// This needs to be included in each header file.
#pragma once

#include <string>
class Person
{
public: //declaring functions here
// A Rule of Thumb when designing classes is to have a default constructor, regular constructor, and a destructor.
    Person();   //default Constructor
    Person(const std::string& name, int age);   //regular
    ~Person();  //destructor

    int getAge() const;
    const std::string& getName() const;

    void printInfo() const;//Print out the name and age of the person.

    void setName(const std::string& newName);
    void setAge(int newAge);

    static int combinedAge(Person** x, int size); // Print the combined Age of everyone pointed to by x
    static void birthday(Person& x); // Increases the Person's Age by 1.
private:
    std::string name_;

    int* age_; // age_ should be a dynamically allocated. here, the pointer is declared

};


