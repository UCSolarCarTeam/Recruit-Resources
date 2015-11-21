#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTime>

#include "LogFileReader.h"
#include <iostream>

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
    unsigned int allowedCharLength = 15;
    std::string allowedChars [allowedCharLength] = {"1","2","3","4","5","6","7","8","9","0",":",",",".","-"," "};
    bool tempBool;
    for(unsigned int count = 0; count < line.toStdString().length(); count++)
    {
        tempBool = false;
        for(unsigned int count1 = 0; count1 < allowedCharLength; count1++)
        {
            if(allowedChars[count1] == line.toStdString().substr(count,1))
            {
                tempBool = true;
            }
        }
        if(tempBool == false)
        {
            return false;
        }
    }

    //example input= 07:01:07.024, 3.538654, 25.523571
    QStringList lineSplit = line.split(",");
    if(lineSplit.length()!= 3)
        return false;
    QStringList timeSplit = lineSplit[0].split(":");
    if(timeSplit.length()!=3)
        return false;
    QStringList secondSplit = timeSplit[2].split(".");
    if(secondSplit.length()!=2)
        return false;

    QTime time = QTime(timeSplit[0].toInt(),    //hour
                        timeSplit[1].toInt(),   //minute
                        secondSplit[0].toInt(), //second
                        secondSplit[1].toInt());//millisec

    batteryData = BatteryData(time,
                              lineSplit[1].toDouble(),//voltage
                              lineSplit[2].toDouble());//current

    return true;
}
