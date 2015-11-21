#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include "LogFileReader.h"

namespace
{
    const QString TIME_FORMAT = "hh:mm:ss.zzz";
    const int NUMBER_OF_COLUMNS = 3;
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
    QStringList sections = line.split(", ");
    if(sections.length() != NUMBER_OF_COLUMNS)
    {
     return false;
    }

    QString stringTime = sections.at(0);
    batteryData.time = QTime::fromString (stringTime, TIME_FORMAT);

    bool voltageOkay;
    bool currentOkay;

    batteryData.voltage = sections.at(1).toDouble(&voltageOkay);
    batteryData.current = sections.at(2).toDouble(&currentOkay);

    if(!voltageOkay || !currentOkay || !batteryData.time.isValid())
    {
        return false;
    }
    else
    {
        return true;
    }
}
