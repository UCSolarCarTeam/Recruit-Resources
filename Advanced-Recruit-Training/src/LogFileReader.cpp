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
    //Michael u retard didnt do precision check do it when ur sober
    while(!input.atEnd())
    {
        QString line = input.readLine();
        BatteryData batteryData;
        if (!parseLine(line, batteryData))  //! taken before parseline out
        {
            qDebug() << "Error while parsing" << line;
            return false;//previous commented out
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
    QString test=sections.at(1);
    QString test1=sections.at(2);
    QStringList sectvolt=test.split(".");
    QStringList sectamp=test.split(".");
    QString sectvolt2=sectvolt.at(1);
    QString sectamp2=sectamp.at(1);
    if(sections.size()!=3)
    {
        return false;
    }
    if(sectvolt2.length()!=6)
    {
        return false;
    }
    if(sectamp2.length()!=6)
    {
        return false;
    }
    if(sections.contains("[Aa-Zz]"))//make sure it doesnt contain alphabetical characters
    {
        return false;//bad
    }
    QString timeString = sections.at(0);
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);
    if(sections.at(1).contains("[^Aa-Zz]"))//look to see if it contains any letters
    {

        return false;//bad
    }
    if(sections.at(2).contains("[^Aa-Zz]"))//look for alphabet
    {
        return false;//bad
    }


    batteryData.voltage = sections.at(1).toDouble();//convert to double
    batteryData.current = sections.at(2).toDouble();//convert to double
    QTextStream(stdout) << "Voltage: " << batteryData.voltage;
    QTextStream(stdout) <<"currentt " << batteryData.current;


    return true;//:)

}

