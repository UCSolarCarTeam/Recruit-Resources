#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const QString STRING_TIME_FORMAT= "hh:mm:ss.zzz";
    const QString BATDATA_DELIMITER= ", ";
    const int COLUMNS = 3;
}

LogFileReader::LogFileReader()
{
}

LogFileReader::~LogFileReader()
{
}

bool LogFileReader::readAll(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file" << fileName;
        return false;
    }

    QTextStream input(&file);
    while(!input.atEnd())
    {
        QString line = input.readLine();
        BatteryData batteryData;
        if (!parseLine(line, batteryData))
        {
            qDebug() << "Error while parsing" << line;
            return false;
        }
        else
        {
            emit batteryDataReceived(batteryData);
        }
    }

    return true;
}

bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{
    QStringList sections = line.split(BATDATA_DELIMITER);

    if(sections.size()!=3)
    {
        return false;
    }

    QString timeString = sections.at(0);

    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    bool voltageok=true;

    bool currentok=true;

    batteryData.voltage = sections.at(1).toDouble(&voltageok);

    batteryData.current = sections.at(2).toDouble(&currentok);
    batteryData.time.isValid();

    if(!batteryData.time.isValid()){
        return false;
 }
    if(voltageok==false){
        return false;
    }
    if(currentok==false){
        return false;
    }

    return true;
}
