#include <Member.h>

Member::Member(QString first, QString last, int gradYr): firstName(first), lastName(last), gradYear(gradYr){ }

QString Member::getFirstName(){
    return firstName;
};

QString Member::getLastName(){
    return lastName;
};

int Member::getGradYear(){
    return gradYear;
};

bool Member::isEqual(const Member& other)
{
    return (firstName == other.firstName) && (lastName == other.lastName) && (gradYear == other.gradYear);
}
