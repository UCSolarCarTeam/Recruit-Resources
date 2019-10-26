#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <iostream>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    double initialAmpHours;
    double remainingAmpHours = BATTERY_AMP_HOUR_CAPACITY - initialAmpHours;
    double usedAmpHours = BATTERY_AMP_HOUR_CAPACITY - remainingAmpHours;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    initialAmpHours = initialStateOfChargePercent_ /100.0 * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    //double initialAmpHours = initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY;

    return initialAmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{

    if(data_.current < 0) return true;
    return false;   //assuming positive current is not charging
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    remainingAmpHours = BATTERY_AMP_HOUR_CAPACITY - initialAmpHours;
    std::cout<<" \n<< "<<remainingAmpHours<<std::endl;

    double hoursTill;
    if(isCharging()){
        hoursTill = 0.0 - 61.5 / data_.current;
    }
    else
        hoursTill = remainingAmpHours / data_.current;

    int milliseconds = hoursTill * 3600000; int remainingMilis;
    int hours = milliseconds / 3600000; remainingMilis = milliseconds % 3600000;
    int minutes = remainingMilis / 60000; remainingMilis = milliseconds % 60000;
    int seconds = remainingMilis / 1000; remainingMilis = milliseconds % 1000;
    int mili = remainingMilis;

    return QTime(hours, minutes, seconds, mili);
    //return QTime::currentTime();
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Q_UNUSED(batteryData);
    data_ = batteryData;

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
