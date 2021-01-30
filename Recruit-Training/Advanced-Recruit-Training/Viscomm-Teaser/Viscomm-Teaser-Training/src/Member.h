#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QJsonObject>

class Member {
private:
    QString firstName, lastName;
    int gradYear;
public:
    Member(QString first, QString last, int gradYr);
    Member() {};
    QString getFirstName();
    QString getLastName();
    int getGradYear();
    bool isEqual(const Member& other);
};


#endif // MEMBER_H
