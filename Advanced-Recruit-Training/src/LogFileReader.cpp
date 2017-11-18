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
    bool voltageExists = true;
    bool currentExists = true;
    bool timeExists = true;
    bool voltageSyntax = true;
    bool currentSyntax = true;
    bool properSize = true;
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
        //return false;
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
        /*else if(properSize == false)
        {
            qDebug() << "Error, not proper size" << line;
        }
        else if(timeExists == false)
        {
            qDebug() << "Error, time is blank" << line;
        }*/
        else if(!batteryData.time.isValid())
        {
            qDebug() << "Error, time argument has incorrect syntax" << line;
        }
        /*

        else if(voltageExists == false)       //test if voltage exists
        {
            qDebug() << "Error, voltage does not exist" << line;

        }
        else if(currentExists == false)       //test if voltage exists
        {
            qDebug() << "Error, current does not exist" << line;

        }
        else if(voltageSyntax == false)
        {
            qDebug() << "Error, voltage syntax is incorrect" << line;
        }
        else if(currentSyntax == false)
        {
            qDebug() << "Error, current syntax is incorrect" << line;
        }*/

        else
        {

            // This is how to send out a signal in QT using the emit keyword.
            // This line notifies the classes listening to this signal
            // that battery data has been received.
            emit batteryDataReceived(batteryData);
        }
    }
    return true;
}

/* File input is a csv file in the format of hh:mm:ss:zzz, voltage, current.
 * Negative current values denote a charging battery.
 * Need to implement error checking for the correct number of values and
 * that the conversion from string to double is sucessful.*/
bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{
    QStringList sections = line.split(BATDATA_DELIMITER);
    if(sections.size() != 3)
        return false;

    if(sections.at(0).isNull())
    {
        return false;
    }
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);
    if(sections.at(1).isNull())
    {
        return false;
    }
    batteryData.voltage = sections.at(1).toDouble();
    if(sections.at(2).isNull())
    {
        return false;
    }
    batteryData.current = sections.at(2).toDouble();

    return true;

}
