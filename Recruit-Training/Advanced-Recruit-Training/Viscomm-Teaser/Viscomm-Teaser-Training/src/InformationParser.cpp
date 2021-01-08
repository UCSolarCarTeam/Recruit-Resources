#include "InformationParser.h"

InformationParser::InformationParser()
{

}

bool InformationParser::readJSON()
{
    QFile loadFile(QStringLiteral("../../CarData.json"));

       if (!loadFile.open(QIODevice::ReadOnly)) {
           return false;
       }

       QByteArray CarData = loadFile.readAll();

       QJsonDocument CarDoc(QJsonDocument::fromJson(CarData));
       CarObj = CarDoc.object();
       VisMem = CarDoc["viscommTeamMembers"].toArray();

       return true;
}

QJsonObject InformationParser::getObj()
{
    return CarObj;
}


QJsonArray InformationParser::getMem()
{
    return VisMem;
}
