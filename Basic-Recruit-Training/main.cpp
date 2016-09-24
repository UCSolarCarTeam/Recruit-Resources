#include <iostream> //Imports cout
#include <sstream>
#include <string>
#include "Person.h"

void compareAnswers(const std::string myAnswer, const std::string correctAnswer)
{
    if(myAnswer.compare(correctAnswer) != 0)
    {
        std::cout << "Incorrect." << std::endl;
        std::cout << "Expected: " << correctAnswer << std::endl;
        std::cout << "You got: " << myAnswer << std::endl;
    }
    else
    {
        std::cout << "Correct." << std::endl;
    }
}
//Swaps a & b.
void mySwap(int& a, int& b)
{
}
//Using y++ or similar variants is not allowed for this function.
void myIncrement(int* x, int& y)
{
}

int main()
{
    int a = 5;
    int b = 6;
    int* c = 0;
    mySwap(a, b);
    myIncrement(c, a);

    std::stringstream swapIncrementAnswer;
    std::cout << "Checking Swap and Increment: " << std::endl;
    swapIncrementAnswer << "a is " << a << ", b is " << b;
    std::cout << swapIncrementAnswer.str() << std::endl;
    const std::string correctSwapIncrementAnswer = "a is 7, b is 5";
    compareAnswers(swapIncrementAnswer.str(), correctSwapIncrementAnswer);

    Person Bill;
    Bill.setName("Bill");
    Bill.setAge(18);
    Bill.printInfo();

    Person Bob("Bob", 30);
    Bob.printInfo();
    Person* Joe = new Person("Joe", 15);
    Joe->printInfo();

    Person* personArray[] = {&Bill, &Bob, Joe};
    std::stringstream myCombinedAgeAnswer;
    myCombinedAgeAnswer << "The combined age of Bill, Bob, and Joe is: " << Person::combinedAge(personArray, sizeof(personArray)/sizeof(Person*));
    const std::string correctCombinedAgeAnswer = "The combined age of Bill, Bob, and Joe is: 63";

    std::cout << "Checking Person::combinedAge:" << std::endl;
    std::cout << myCombinedAgeAnswer.str() << std::endl;
    compareAnswers(myCombinedAgeAnswer.str(), correctCombinedAgeAnswer);

    Person::birthday(Bill);
    std::stringstream myBirthdayAnswer;

    myBirthdayAnswer << "It was Bill's Birthday, he is now " << Bill.getAge();
    const std::string correctBirthdayAnswer = "It was Bill's Birthday, he is now 19";

    std::cout << "Checking Person::Birthday:" << std::endl;
    std::cout << myBirthdayAnswer.str().c_str()<< std::endl;
    compareAnswers(myBirthdayAnswer.str(), correctBirthdayAnswer);

    return 0;
}
