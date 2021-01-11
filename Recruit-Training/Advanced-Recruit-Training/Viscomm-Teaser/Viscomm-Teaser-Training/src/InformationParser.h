#ifndef INFORMATIONPARSER_H
#define INFORMATIONPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>

class InformationParser
{
public:
    InformationParser();
    QJsonObject readFile();
    bool readJSON();
    QString getOwner() const;
    QString getType() const;
    QString getCarName() const;
    int getBatteryPercentage() const;
    QString getColor() const;
    QString getLocation() const;
    QJsonArray getTeamMembers() const;
    void updateTeamMembers(QJsonArray &updatedArray);
    bool updateJSON();

private:
    //Place your JSON variables here
    QString owner_;
    QString type_;
    QString carName_;
    int batteryPercentage_;
    QString color_;
    QString location_;
    QJsonArray teamMembers_;
};

#endif // INFORMATIONPARSER_H
