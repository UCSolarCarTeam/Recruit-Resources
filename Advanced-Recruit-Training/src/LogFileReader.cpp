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
            // This is how to send out a signal in QT using the emit keyword.
            // This line notifies the classes listening to this signal
            // that battery data has been received.
            emit batteryDataReceived(batteryData);
        }
    }

    return true;
}

bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{
    QStringList sections = line.split(BATDATA_DELIMITER);

    // line must have 3 comma-separated values
    if (sections.size() != COLUMNS)
    {
        return false;
    }

    // check if time, voltage and current is valid
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);
    bool voltageIsValid;
    bool currentIsValid;
    batteryData.voltage = sections.at(1).toDouble(&voltageIsValid);
    batteryData.current = sections.at(2).toDouble(&currentIsValid);

    if (!batteryData.time.isValid() || !voltageIsValid || !currentIsValid)
    {
        return false;
    }

    return true;

}
