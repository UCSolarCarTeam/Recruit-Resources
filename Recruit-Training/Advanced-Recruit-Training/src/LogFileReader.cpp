#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTime>

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

bool LogFileReader::parseLine(const QString& line, BatteryData& batteryData) const
{

    QStringList sections = line.split(BATDATA_DELIMITER);
    bool ok;
    if(sections.length()!=3){
        return false;
    }
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    batteryData.voltage = sections.at(1).toDouble(&ok);
    if(!ok){
        return false;
    }
    batteryData.current = sections.at(2).toDouble(&ok);
    if(!ok){
        return false;
    }

    if(batteryData.time.isValid()){
        return true;
    }
    else{
        return false;
    }

}
