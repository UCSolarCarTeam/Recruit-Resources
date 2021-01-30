#ifndef INFORMATIONPARSER_H
#define INFORMATIONPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QVector>
#include <QJsonDocument>
#include <QInputDialog>
#include <Member.h>

class InformationParser
{
public:
    InformationParser();
    bool readJSON();
    QString getOwner() const, getType() const, getCarName() const, getColor() const, getLocation() const;
    double getBatteryPercentage() const;
    QVector<Member> getViscommTeamMembers() const;
    bool addMember(QString first, QString last, int year), removeMember(QString first, QString last, int year);
    int searchForMember(Member& target);
private:
    //Place your JSON variables here
    QString owner, type, carName, color, location;
    double batteryPercentage;
    QVector<Member> viscommTeamMembers;
};

#endif // INFORMATIONPARSER_H
