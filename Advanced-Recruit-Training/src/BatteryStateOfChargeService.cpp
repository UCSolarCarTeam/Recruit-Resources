#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <qdebug.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;

}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100) + additionalAmpHours_;
}
bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ < 0)
        return true;
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    if(current_ < 0) //charging
        return (timeToCompletion_.addMSecs((totalAmpHoursUsed()/-current_)*3600000));
    else    //depleting
        return (timeToCompletion_.addMSecs(((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_)*3600000));
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    timeToCompletion_.setHMS(0, 0, 0, 0);
    timeDifference_ = (double) (time_.msecsTo(batteryData.time)/3600000);   //time difference is 0 for the first and then time_ is the previous for the next
    currentAverage_ = (current_ + batteryData.current)/2;
    time_ = batteryData.time;
    current_ = batteryData.current;
    additionalAmpHours_ += currentAverage_*timeDifference_;
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
