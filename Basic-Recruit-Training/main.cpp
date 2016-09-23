#include <iostream> //Imports cout
#include <sstream>
#include <string>
#include "Person.h"

void compareAnswers(const std::string myAnswer, const std::string correctAnswer)
{
    if(myAnswer.compare(correctAnswer) != 0)
    {
        std::cout << "Incorrect." << std::endl;
        std::cout << "Expected: " << correctAnswer;
    }
    else
    {
        std::cout << "Correct." << std::endl;
    }
}

int main()
{
    Person Bill;
    Bill.setName("Bill");
    Bill.setAge(18);
    Bill.printInfo();

    Person Bob("Bob", 30);
    Bob.printInfo();
    Person* Joe = new Person("Joe", 15);
    Joe->printInfo();

    Person* personArray[] = {&Bill, &Bob, Joe};
    std::stringstream myFirstAnswer;
    myFirstAnswer << "The combined age of Bill, Bob, and Joe is: " << Person::combinedAge(personArray);
    const std::string correctFirstAnswer = "The combined age of Bill, Bob, and Joe is: 63";

    std::cout << myFirstAnswer.str() << std::endl;
    compareAnswers(myFirstAnswer.str(), correctFirstAnswer);

    Person::birthday(Bill);
    std::stringstream mySecondAnswer;

    mySecondAnswer << "It was Bill's Birthday, he is now " << Bill.getAge();
    const std::string correctSecondAnswer = "It was Bill's Birthday, he is now 19";

    std::cout << mySecondAnswer.str().c_str() << std::endl;
    compareAnswers(mySecondAnswer.str(), correctSecondAnswer);

    return 0;
}
