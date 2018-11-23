#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

namespace
{
    const QString STRING_TIME_FORMAT= "hh:mm:ss.zzz";
    const QString BATDATA_DELIMITER= ", ";
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
            // return false;
        }
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
    if(sections.length() != 3)
        return false;

    bool valid, voltageValid, currentValid;

    QString timeString = sections.at(0);
    QTime time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    double voltage = sections.at(1).toDouble(&voltageValid);
    double current = sections.at(2).toDouble(&currentValid);

    valid = (time.isValid() && voltageValid && currentValid);

    if(valid)
    {
        batteryData.time = time;
        batteryData.voltage = voltage;
        batteryData.current = current;
    }
    return valid;
}
