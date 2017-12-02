#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QRegExp>

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
    { // check for exact format "hh:mm:ss.zzz, voltage, current"
        // time must be hh:mm:ss.zzz
        QString regexHour = "([0-1]\\d|2[0-3])", regexMinSec = "[0-5]\\d", regexMSec = "\\d+";
        QString regexTime = regexHour + ":" + regexMinSec + ":" + regexMinSec + "\\." + regexMSec;

        // voltage must be a positive number, current can be any number
        QString regexVoltage = "\\d+.\\d+", regexCurrent = "(-\\d|\\d)+\\.\\d+";

        // putting it all together
        QString regexItem = QString("(^%1, %2, %3$)").arg(regexTime, regexVoltage, regexCurrent);

        QRegExp rxItem(regexItem);
        if (rxItem.indexIn(line) == -1) {
            return false;
        }
    }

    QStringList sections = line.split(BATDATA_DELIMITER);

    QString timeString = sections.at(0);
    
    batteryData.time = QTime::fromString(timeString, STRING_TIME_FORMAT);

    batteryData.voltage = sections.at(1).toDouble();

    batteryData.current = sections.at(2).toDouble();

    return true;

}
