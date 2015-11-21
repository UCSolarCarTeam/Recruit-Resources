#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include "LogFileReader.h"

LogFileReader::LogFileReader()
{
}

LogFileReader::~LogFileReader()
{
}

namespace
{
    QString STRING_TO_QTIME = "hh:mm:ss.zzz";
    QString BATDATA_DELIMITER = ",";
}

bool LogFileReader::readAll(const QString& fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Unable to open file" << fileName;
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
            // This is how to send out a signal in QT using the emit keyword.
            // This line notifies how any classes listening to this signal
            // that battery data has been received.
            emit batteryDataReceived(batteryData);
        }
    }
    return true;
}

// File input is a csv file in the format of hh:mm:ss:zzz, voltage, current
bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{
    // TODO implement this first
    QStringList column = line.split(BATDATA_DELIMITER);
    if(column.length() != 3)
    {
           return false;
    }
    QString timeString = column.at(0);

    batteryData.time = QTime::fromString(timeString, STRING_TO_QTIME);

    bool currentOkay;
    bool voltageOkay;

    batteryData.voltage = column.at(1).toDouble(&voltageOkay);
    batteryData.current = column.at(2).toDouble(&currentOkay);

    if(currentOkay && voltageOkay && batteryData.time.isValid())
    {
        return true;
    }
    else
    {
        return false;
    }
}
