#include "BatteryStateOfChargeService.h"
#include <math.h>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOUR_IN_MILLISECONDS = 3600000;
    const int MINUTE_IN_MILLISECONDS = 60000;
    const int SECOND_IN_MILLISECONDS = 1000;
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
    return totalAmphoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(currentNow_ < 0)
        return true;
    else
        return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double totalHoursRemaining, millisecondsRemaining;
    int hours, minutes, seconds, milliseconds;

    if(isCharging())
        totalHoursRemaining = totalAmpHoursUsed() / currentNow_ * -1;
    else
        totalHoursRemaining = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / currentNow_;

    //Checking for total hours to be in between 0 and 24
    while(totalHoursRemaining > 24)
        totalHoursRemaining -= 24;

    //Converting totalHoursRemaining into hours, minutes, seconds, milliseconds
    hours = floor(totalHoursRemaining);
    millisecondsRemaining = (totalHoursRemaining - hours) * HOUR_IN_MILLISECONDS;
    minutes = floor(millisecondsRemaining / MINUTE_IN_MILLISECONDS);
    millisecondsRemaining = millisecondsRemaining - (minutes * MINUTE_IN_MILLISECONDS);
    seconds = floor(millisecondsRemaining / SECOND_IN_MILLISECONDS);
    millisecondsRemaining = millisecondsRemaining - (seconds * SECOND_IN_MILLISECONDS);
    milliseconds = floor(millisecondsRemaining);

    QTime timeRemaining(hours, minutes, seconds, milliseconds);
    return timeRemaining;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    //Calculating inital Amphours used
    double initialAmphoursUsed;
    initialAmphoursUsed = initialStateOfChargePercent_ / 100 * BATTERY_AMP_HOUR_CAPACITY;

    double changeInTimeMSecs, changeInTimeHours;

    currentPrev_ = currentNow_;
    currentNow_ = batteryData.current;

    timePrev_ = timeNow_;
    timeNow_ = batteryData.time;

    changeInTimeMSecs = timePrev_.msecsTo(timeNow_);
    changeInTimeHours = changeInTimeMSecs / HOUR_IN_MILLISECONDS;

    currentAmphoursUsed_ = ((currentNow_ + currentPrev_) / 2) * changeInTimeHours;
    totalAmphoursUsed_ += currentAmphoursUsed_ + initialAmphoursUsed;

    if(totalAmphoursUsed_ != initialAmphoursUsed)
    {
        totalAmphoursUsed_ = totalAmphoursUsed_ - initialAmphoursUsed;
    }
}
