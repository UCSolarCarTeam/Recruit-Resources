#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

namespace
{
    const QString STRING_TIME_FORMAT= "hh:mm:ss.zzz";
    const QString BATDATA_DELIMITER= ",";
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
    if(!lineIsOfProperFormat(sections))
    {
        return false;
    }

    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    batteryData.voltage = sections.at(1).toDouble();

    batteryData.current = sections.at(2).toDouble();

    return true;

}

bool LogFileReader::lineIsOfProperFormat(const QStringList sections) const
{
    if(sections.size() != 3)
    {
        return false;
    }

    if(!isTimeValid(sections.at(0)))
    {
        return false;
    }

    bool voltageOk = false, currentOk = false;
    sections.at(1).toDouble(&voltageOk);
    sections.at(2).toDouble(&currentOk);
    if(!voltageOk || !currentOk)
    {
        return false;
    }

    return true;
}

bool LogFileReader::isTimeValid(const QString &timeValue) const
{

    QStringList sections = timeValue.split(":");
    if(sections.size() != 3) {
        return false;
    }

    bool hoursOk = false, minutesOk = false, secondsOk = false;
    int hours = sections.at(0).toInt(&hoursOk, 10), minutes = sections.at(1).toInt(&minutesOk, 10);
    double seconds = sections.at(2).toDouble(&secondsOk);

    if(!hoursOk || hours < 0)
    {
        return false;
    }

    if(!minutesOk || minutes < 0)
    {
        return false;
    }

    if(!secondsOk || seconds < 0 || seconds >= 60)
    {
        return false;
    }

    return true;
}
