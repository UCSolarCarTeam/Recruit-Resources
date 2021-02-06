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
    if (doc.isNull()) 
    {
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
        owner_ = json["owner"].toString();
        type_ = json["type"].toString();
        carName_ = json["carName"].toString();
        batteryPercentage_ = json["batteryPercentage"].toDouble();
        color_ = json["color"].toString();
        location_ = json["location"].toString();

        QJsonArray teamMemberArray = json["viscommTeamMembers"].toArray();
        viscommTeamMembers_.clear();
        viscommTeamMembers_.reserve(teamMemberArray.size());
        for(QJsonValueRef a : teamMemberArray)
        {
           QJsonObject m = a.toObject();
           Member member(m["firstName"].toString(), m["lastName"].toString(), m["gradYear"].toString().toInt());
           viscommTeamMembers_.append(member);
        }

        return true;
    }

    return false;
}

QString InformationParser::getOwner() const
{
    return owner_;
};

QString InformationParser::getType() const
{
    return type_;
};

QString InformationParser::getCarName() const
{
    return carName_;
};

QString InformationParser::getColor() const
{
    return color_;
};

QString InformationParser::getLocation() const
{
    return location_;
};

double InformationParser::getBatteryPercentage() const
{
    return batteryPercentage_;
};

QVector<Member> InformationParser::getViscommTeamMembers() const
{
    return viscommTeamMembers_;
};

bool InformationParser::addMember(QString first, QString last, int year)
{
    Member newbie(first, last, year);
    int result = searchForMember(newbie);
    if(result == -1)
    {
        viscommTeamMembers_.append(newbie);
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
        viscommTeamMembers_.remove(result);
        return true;
    }
    return false;
}

int InformationParser::searchForMember(Member& target)
{
    int size = viscommTeamMembers_.size();
    for(int i = 0; i < size ; ++i)
    {
        if(target.isEqual(viscommTeamMembers_[i]))
        {
            return i;
        }
    }

    return -1;
}
