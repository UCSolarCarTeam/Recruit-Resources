#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

namespace
{
    const QString TIME_FORMAT = "hh:mm:ss.zzz";
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
    //example input= 07:01:07.024, 3.538654, 25.523571
    bool convertedOkay;
    QStringList lineSplit = line.split(",");
    if(lineSplit.length() != 3)
    {
        return false;
    }

    QTime time = QTime::fromString(lineSplit[0],TIME_FORMAT);
    if(!time.isValid())
    {
        return false;
    }

    double voltage = lineSplit[1].toDouble(&convertedOkay);
    if(!convertedOkay)
    {
        return false;
    }

    double current = lineSplit[2].toDouble(&convertedOkay);
    if(!convertedOkay)
    {
        return false;
    }

    batteryData = BatteryData(time, voltage, current);
    return true;
}
