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

    if(sections.length() != COLUMNS){
        return false;
    }

    QString timeString = sections.at(0);
/*
    if(timeString[2] != ":" || timeString[5] != ":" || timeString[8] != "."){
        return false;
    }
    for(int i = 0; i < timeString.length(); i++){
        if(timeString[i] == "a"){   //maybe change this later to be less hardcoded
            return false;
        }

    }*/

//Qtime isValid thing, add seconds and milliseconds/1000


    QTime time1 = QTime::fromString(timeString, STRING_TIME_FORMAT);
    batteryData.time = time1;
    bool isTimeValid = QTime::isValid(time1.hour(), time1.minute(), (time1.second() + (time1.msec()/1000)));
    bool flag1;
    bool flag2;
    batteryData.voltage = sections.at(1).toDouble(&flag1);
    batteryData.current = sections.at(2).toDouble(&flag2);
    if(flag1 && flag2 && isTimeValid){
        return true;
    }else{
        return false;
    }



}
