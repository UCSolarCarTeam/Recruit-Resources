#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <iostream>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    double remainingAmpHours;
    int semaphore = 0;

    double oldCurrent = 0;
    QTime oldTime;

}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    remainingAmpHours = initialStateOfChargePercent_ /100.0 * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    //double initialAmpHours = initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY;

    return BATTERY_AMP_HOUR_CAPACITY - remainingAmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(data_.current < 0) return true;
    return false;   //assuming positive current is not charging
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double hoursTill;
    if(isCharging()){
        hoursTill = 0.0 - (BATTERY_AMP_HOUR_CAPACITY - remainingAmpHours) / data_.current;
    }
    else{
        hoursTill = remainingAmpHours / data_.current;
    }

    int milliseconds = hoursTill * 3600000; int remainingMilis;
    int hours = milliseconds / 3600000 % 24; remainingMilis = milliseconds % 3600000;
    int minutes = remainingMilis / 60000 % 60; remainingMilis = milliseconds % 60000;
    int seconds = remainingMilis / 1000 % 60; remainingMilis = milliseconds % 1000;
    int mili = remainingMilis;

    return QTime(hours, minutes, seconds, mili);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Q_UNUSED(batteryData);
    data_ = batteryData;

    if(!semaphore){
        oldCurrent = abs(data_.current);
        oldTime = data_.time;
        semaphore = 1;
        return;
    }

    double newCurrent = abs(data_.current);
    QTime newTime = data_.time;

    double oldHour = oldTime.hour();
    double oldMinute = oldTime.minute();
    double oldSec = oldTime.second();
    double oldMili = oldTime.msec();

    double newHour = newTime.hour();
    double newMinute = newTime.minute();
    double newSec = newTime.second();
    double newMili = newTime.msec();

    double totalHoursOld = oldHour + oldMinute / 60.0 + oldSec / 3600.0 + oldMili / 3600000.0;
    double totalHoursNew = newHour + newMinute / 60.0 + newSec / 3600.0 + newMili / 3600000.0;
    double totalHours = totalHoursNew - totalHoursOld;

    double usedAmpHours = (newCurrent + oldCurrent) / 2.0 * totalHours;

    if(isCharging())
        remainingAmpHours += usedAmpHours;
    else
        remainingAmpHours -= usedAmpHours;

    oldCurrent = newCurrent;
    oldTime = newTime;

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
