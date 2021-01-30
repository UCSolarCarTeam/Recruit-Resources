#include "InformationParser.h"

InformationParser::InformationParser()
{
    
}

bool InformationParser::readJSON()
{
    QFile inFile("../../CarData.json");
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()) {
        return false;
    }

    QJsonObject json = doc.object();
    if(json.contains("owner") && json["owner"].isString() &&
       json.contains("type") && json["type"].isString() &&
       json.contains("carName") && json["carName"].isString() &&
       json.contains("batteryPercentage") && json["batteryPercentage"].isDouble() &&
       json.contains("color") && json["color"].isString() &&
       json.contains("location") && json["location"].isString() &&
       json.contains("viscommTeamMembers") && json["viscommTeamMembers"].isArray())
    {
        owner = json["owner"].toString();
        type = json["type"].toString();
        carName = json["carName"].toString();
        batteryPercentage = json["batteryPercentage"].toDouble();
        color = json["color"].toString();
        location = json["location"].toString();

        QJsonArray teamMemberArray = json["viscommTeamMembers"].toArray();
        viscommTeamMembers.clear();
        viscommTeamMembers.reserve(teamMemberArray.size());
        for(QJsonValueRef a : teamMemberArray)
        {
           QJsonObject m = a.toObject();
           Member member(m["firstName"].toString(), m["lastName"].toString(), m["gradYear"].toString().toInt());
           viscommTeamMembers.append(member);
        }

        return true;
    }

    return false;
}

QString InformationParser::getOwner() const{
    return owner;
};

QString InformationParser::getType() const{
    return type;
};

QString InformationParser::getCarName() const{
    return carName;
};

QString InformationParser::getColor() const{
    return color;
};

QString InformationParser::getLocation() const{
    return location;
};

double InformationParser::getBatteryPercentage() const{
    return batteryPercentage;
};

QVector<Member> InformationParser::getViscommTeamMembers() const{
    return viscommTeamMembers;
};

bool InformationParser::addMember(QString first, QString last, int year)
{
    Member newbie(first, last, year);
    int result = searchForMember(newbie);
    if(result == -1)
    {
        viscommTeamMembers.append(newbie);
        return true;
    }
    return false;
}

bool InformationParser::removeMember(QString first, QString last, int year)
{
    Member target(first, last, year);
    int result = searchForMember(target);
    if(result > -1)
    {
        viscommTeamMembers.remove(result);
        return true;
    }
    return false;
}

int InformationParser::searchForMember(Member& target)
{
    int size = viscommTeamMembers.size();
    for(int i = 0; i < size ; ++i)
    {
        if(target.isEqual(viscommTeamMembers[i]))
            return i;
    }

    return -1;
}
