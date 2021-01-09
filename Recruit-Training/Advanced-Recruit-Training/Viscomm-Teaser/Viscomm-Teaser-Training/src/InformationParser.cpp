#include "InformationParser.h"

InformationParser::InformationParser()
{

}

QJsonObject InformationParser::readFile() 
{
	QFile inputFile("../../CarData.json");
	
	if(!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) 
	{
		qDebug() << inputFile.errorString();
		return {};
	}
	
	QJsonParseError JsonParseError;
	QJsonDocument  myDocument = QJsonDocument::fromJson(inputFile.readAll(), &JsonParseError);
	if(myDocument.isNull()) 
	{
		qDebug() << JsonParseError.errorString();
		return {};
	}
	inputFile.close();
	
	QJsonObject documentObject;
	if(myDocument.isObject()) 
	{
		documentObject = myDocument.object();
	} else {
		qDebug() << "Expected an object to be containd in the file";
		return {};
	}
	return documentObject;
}

bool InformationParser::readJSON()
{
	QJsonObject dObject = readFile();
	
	if(dObject.isEmpty())
		return false;
	
	Q_ASSERT(!(dObject.value("owner").isUndefined() || dObject.value("type").isUndefined()
    || dObject.value("carName").isUndefined() || dObject.value("batteryPercentage").isUndefined()
    || dObject.value("color").isUndefined() || dObject.value("location").isUndefined()
    || dObject.value("viscommTeamMembers").isUndefined()));
	
	owner_ = dObject["owner"].toString();
	type_ = dObject["type"].toString();
	carName_ = dObject["carName"].toString();
	batteryPercentage_ = dObject["batteryPercentage"].toInt();
	color_ = dObject["color"].toString();
	location_ = dObject["location"].toString();
	teamMembers_ = dObject["viscommTeamMembers"].toArray();

    return true;
}

QString InformationParser::getOwner() const 
{
	return owner_;
}

QString InformationParser::getType() const 
{
	return type_;
}

QString InformationParser::getCarName() const 
{
	return carName_;
}

int InformationParser::getBatteryPercentage() const 
{
	return batteryPercentage_;
}

QString InformationParser::getColor() const 
{
	return color_;
}

QString InformationParser::getLocation() const 
{
	return location_;
}

QJsonArray InformationParser::getTeamMembers() const 
{
	return teamMembers_;
}

void InformationParser::updateTeamMembers(QJsonArray &updatedArray) 
{
	teamMembers_ = updatedArray;
	if(!updateJSON()) 
	{
		qDebug() << "Error Updating JSON file.";
		exit(1);
	}
}

bool InformationParser::updateJSON() 
{
	QJsonObject dObject = readFile();
	
	if(dObject.isEmpty())
		return false;
	
	QFile inputFile("../../CarData.json");
	dObject["viscommTeamMembers"] = teamMembers_;
	QJsonDocument JsonDocument = QJsonDocument(dObject);
	
	if(!(inputFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate))) 
	{
		return false;
	}
	inputFile.write(JsonDocument.toJson());
	inputFile.close();
	
	return true;
}
