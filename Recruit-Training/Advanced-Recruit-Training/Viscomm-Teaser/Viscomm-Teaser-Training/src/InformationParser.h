#ifndef INFORMATIONPARSER_H
#define INFORMATIONPARSER_H

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QString>
#include <QDebug>

class InformationParser
{
public:
    InformationParser();
    bool readJSON();
    QJsonObject getObj();
    QJsonArray getMem();
private:
    //Place your JSON variables here
    QJsonObject  CarObj;
    QJsonArray VisMem;
};

#endif // INFORMATIONPARSER_H
