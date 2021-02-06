#include <Member.h>

Member::Member(QString first, QString last, int gradYr): firstName_(first), lastName_(last), gradYear_(gradYr)
{ 
    
}

QString Member::getFirstName() const
{
    return firstName_;
};

QString Member::getLastName() const
{
    return lastName_;
};

int Member::getGradYear() const
{
    return gradYear_;
};

bool Member::isEqual(const Member& other)
{
    return (firstName_ == other.firstName_) && (lastName_ == other.lastName_) && (gradYear_ == other.gradYear_);
}
