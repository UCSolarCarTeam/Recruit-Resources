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
    QStringList splitLine = line.split(", ");
      if(splitLine.length() != 3)
        {
           return false;
        }

     QString time = splitLine.at(0);
     batteryData.time = QTime::fromString(time, "hh:mm:ss.zzz");

     batteryData.voltage = splitLine.at(1).toDouble();
     batteryData.current = splitLine.at(2).toDouble();



    // This is here to the compiler happy. Otherwise the compile
    // will have an error warning about an unused variable. Remove this
    // when you use it.
   // Q_UNUSED(line);
    //Q_UNUSED(batteryData);
    return true;
}
