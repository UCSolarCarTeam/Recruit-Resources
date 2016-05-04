/** 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 
 *  of the License, or (at your option) any later version.
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General 
 *  Public License along with the University of Calgary Solar Car 
 *  Team New Recruit Exercise. If not, see 
 *  <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */
#include <QString>
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>
#include <math.h>
#include <cstring>
#include <string>
namespace
{
const QString COMMA = ",";
const QString TIMEFORMAT = "hh:mm:ss.zzz";

}
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
    QStringList lines = line.split(COMMA);
    bool ok;
    //I have to split up the time and round up the second into an integer in order for fromString to work
    //Not sure how to use fromString with 3 decimals in second
//    QStringList timelist = lines[0].split(':');
//    double second = timelist[2].toDouble(&ok);
//    second = round(second);
//    timelist[2] = QString::number(second);
//    lines[0]= timelist.join(":");
    QTime time = QTime::fromString(lines[0],TIMEFORMAT);
    if (time.isValid())
    {
        batteryData.time = time;
    }
    batteryData.voltage = lines[1].toDouble();
    batteryData.current = lines[2].toDouble();
    // This is here to the compiler happy. Otherwise the compile
    // will have an error warning about an unused variable. Remove this
    // when you use it.
    return true;
}

