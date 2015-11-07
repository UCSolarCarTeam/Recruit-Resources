#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), newCurrent(0)
{
    ampHours = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-ampHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newCurrent<0)
        return false;
    else
        return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeLeft;


    timeLeft = (BATTERY_AMP_HOUR_CAPACITY-ampHours)/newCurrent;
    timeLeft = timeLeft/MILLISECONDS_TO_HOURS;
    timeLeft = qAbs(timeLeft);

     QTime baseTime (0, 0, 0, 0);
     QTime timeLeftTillDepletionorCharge;
     timeLeftTillDepletionorCharge = baseTime.addMSecs(timeLeft);

    return timeLeftTillDepletionorCharge;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{



    double timeChange;
    double changeInAmpHours;
    QTime previousTime;


    previousCurrent = newCurrent;
    newCurrent = batteryData.current;
     if (previousCurrent == 0) //For the very first line of data
         averageCurrent = newCurrent;
     else
        averageCurrent = (previousCurrent+newCurrent)/2;


    previousTime = newTime;
    newTime = batteryData.time;
    timeChange =previousTime.msecsTo(newTime);
    timeChange = timeChange * MILLISECONDS_TO_HOURS ;

    changeInAmpHours = averageCurrent * timeChange;
    ampHours +=  changeInAmpHours;


}

