#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

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
    // TODO implement this first
    QStringList sections = line.split(",");
    if (sections.length() !=3)
    {
        return false;
    }

    QString timeString = sections.at(0);
    //Converts timestring to time for bat data
    batteryData.time = QTime::fromString(timeString, "hh:mm:ss.zzz");
    //Takes V
    bool voltageOK;
    batteryData.voltage = sections.at(1) .toDouble(&voltageOK);
    //Takes current
    bool currentOK;
    batteryData.current = sections.at(2) .toDouble(&currentOK);
    if (voltageOK && currentOK && batteryData.time.isValid())
    {
        return true;
    }
    else
    {
        return false;
    }
}
