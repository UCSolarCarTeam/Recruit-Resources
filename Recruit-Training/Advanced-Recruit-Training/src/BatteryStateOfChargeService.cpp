#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

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
    return ampHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ < 0)
        return true;
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime time;
    double totalHours;
    int hours;
    int remainingHours=0;
    int minutes;
    int seconds;

    if(isCharging())
        totalHours = -1 * totalAmpHoursUsed() / current_;
    else
        totalHours = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_;

    hours = (int)totalHours;
    minutes = (int)((totalHours - hours) * 60);
    seconds = (int)((totalHours * 60 - hours * 60 - minutes) * 60);

    //uses msec as a place holder for the remaining hours as the hours in QTime could only hold up to 24
    remainingHours = ((int)(totalHours/24)) * 24;
    hours -= remainingHours;

    time.setHMS(hours, minutes, seconds, remainingHours);

    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    current_ = batteryData.current;
    timeOld_ = timeNew_;
    timeNew_ = batteryData.time;

    if(timeOld_.isNull()) //checks if timeOld_ has no a value (first itteration)
        ampHours_ += BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
    else
        ampHours_ += (current_ * timeOld_.secsTo(timeNew_) / 3600);
}
