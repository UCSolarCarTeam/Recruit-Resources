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
        if (!parseLine(line, batteryData))  //! taken before parseline out
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
    QString test=sections.at(1);
    QString test1=sections.at(2);
    QStringList sectVolt=test.split(".");
    QStringList sectAmp=test.split(".");
    QString sectVolt2=sectVolt.at(1);
    QString sectAmp2=sectAmp.at(1);
    if(sections.size() != 3)
    {
        return false;
    }
    if(sectVolt2.length()<6)
    {
        return false;
    }
    if(sectAmp2.length()<6)
    {
        return false;
    }
    if(sections.contains("[Aa-Zz]")) //make sure it doesnt contain alphabetical characters
    {
        return false;
    }
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);
    if(sections.at(1).contains("[^Aa-Zz]")) //look to see if it contains any letters
    {

        return false;
    }
    if(sections.at(2).contains("[^Aa-Zz]")) //look for alphabet
    {
        return false;
    }
    batteryData.voltage = sections.at(1).toDouble(); //convert to double
    batteryData.current = sections.at(2).toDouble(); //convert to double
    return true;
}

