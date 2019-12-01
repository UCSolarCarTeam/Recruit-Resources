#include "BatteryStateOfChargeService.h"
#include <math.h>
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
    double totalHoursRemaining, msRemaining;
    int h, m, s, ms;

    if(isCharging())
        totalHoursRemaining = totalAmpHoursUsed() / currentNow_ * -1;
    else
        totalHoursRemaining = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / currentNow_;

    //Checking for hour to be in between 0 and 24
    while(totalHoursRemaining > 24)
        totalHoursRemaining -= 24;

    //Converting totalHoursRemaining into h, m, s, ms
    h = floor(totalHoursRemaining);
    msRemaining = (totalHoursRemaining - h) * 3600000;
    m = floor(msRemaining / 60000);
    msRemaining = msRemaining - (m * 60000);
    s = floor(msRemaining / 1000);
    msRemaining = msRemaining - (s * 1000);
    ms = floor(msRemaining);

    QTime timeRemaining(h, m, s, ms);
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
    changeInTimeHours = changeInTimeMSecs / 3600000;

    currentAmphoursUsed_ = ((currentNow_ + currentPrev_) / 2) * changeInTimeHours;
    totalAmphoursUsed_ += currentAmphoursUsed_ + initialAmphoursUsed;

    if(totalAmphoursUsed_ != initialAmphoursUsed)
    {
        totalAmphoursUsed_ = totalAmphoursUsed_ - initialAmphoursUsed;
    }
}
