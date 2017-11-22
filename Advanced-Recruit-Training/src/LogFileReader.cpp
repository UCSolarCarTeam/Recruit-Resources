#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

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
    if(sections.size() != 3)
        return false;
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    bool voltageOk;
    bool currentOk;
    batteryData.voltage = sections.at(1).toDouble(&voltageOk);
    batteryData.current = sections.at(2).toDouble(&currentOk);
    if(!batteryData.time.isValid() || !voltageOk || !currentOk)
        return false;
    return true;

}
