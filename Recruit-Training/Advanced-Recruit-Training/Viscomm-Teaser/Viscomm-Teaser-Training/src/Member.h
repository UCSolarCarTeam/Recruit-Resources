#ifndef MEMBER_H
#define MEMBER_H

#include <QString>
#include <QJsonObject>

class Member {
public:
    Member(QString first, QString last, int gradYr);
    Member() {};
    QString getFirstName() const;
    QString getLastName() const;
    int getGradYear() const;
    bool isEqual(const Member& other);

private:
    QString firstName_, lastName_;
    int gradYear_;
};


#endif // MEMBER_H
