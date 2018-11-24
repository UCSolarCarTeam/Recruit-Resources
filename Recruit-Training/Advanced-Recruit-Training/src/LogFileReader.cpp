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

    QString timeString = sections.at(0);
    QTime time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    if(!time.isValid())
    {
        return false;
    }

    if(sections.at(2).contains("[a-zA-Z]+"))
    {
        return false;
    }

    if(sections.at(1).contains("[a-zA-Z]+") || sections.at(1).toDouble() < 0)
    {
        return false;
    }

    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    batteryData.voltage = sections.at(1).toDouble();

    batteryData.current = sections.at(2).toDouble();

    return true;

}
