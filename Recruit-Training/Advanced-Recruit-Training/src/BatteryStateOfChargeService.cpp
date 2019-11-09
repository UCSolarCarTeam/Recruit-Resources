#include "BatteryStateOfChargeService.h"

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
    return amphour_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (currentNew_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    int hours;
    int minutes;
    int seconds;
    int remainingHours;
    double totalTime;

    if (isCharging())
    {
        totalTime =  - amphour_ / currentNew_;
        hours = totalTime;
        minutes = (totalTime - hours) * 60;
        seconds = (totalTime * 60 - hours * 60 - minutes) * 60;
        remainingHours = (hours / 24) * 24;
        hours -= remainingHours;


    }
    else
    {
        totalTime =  (BATTERY_AMP_HOUR_CAPACITY - amphour_) / currentNew_;
        hours = totalTime;
        minutes = (totalTime - hours) * 60;
        seconds = (totalTime * 60 - hours * 60 - minutes) * 60;
        remainingHours = (hours / 24) * 24;
        hours -= remainingHours;

    }

    return QTime(hours, minutes, seconds, remainingHours);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData)
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    currentOld_ = currentNew_;
    currentNew_ = batteryData.current;

    timeOld_ = timeNew_;
    timeNew_ = batteryData.time;

    if (!timeOld_.isNull())
    {
        amphour_ += (currentNew_ + currentOld_) / 2 * timeOld_.msecsTo(timeNew_) / 3600000 ;
    }
    else
    {
        amphour_ +=  BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
    }
}
