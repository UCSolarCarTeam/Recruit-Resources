#include <QTime>
#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_MILLISECONDS = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent),
  totalAmphoursUsed_((initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY) / 100)
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
    return (current_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double totalHoursRemaining;

    if(isCharging())
    {
        totalHoursRemaining = abs(totalAmpHoursUsed() / current_);
    }
    else
    {
        totalHoursRemaining = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_;
    }

    QTime timeRemaining(0, 0, 0, 0);
    int totalMillisecRemaining =  totalHoursRemaining * HOUR_TO_MILLISECONDS;
    timeRemaining = timeRemaining.addMSecs(totalMillisecRemaining);
    return timeRemaining;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    double oldCurrent = current_;
    current_ = batteryData.current;
    QTime oldTime = newTime_;
    newTime_ = batteryData.time;
    double averageCurrent = (oldCurrent + current_) / 2;

    double changeInTimeMseconds = oldTime.msecsTo(newTime_);
    double hour = changeInTimeMseconds / HOUR_TO_MILLISECONDS;
    double currentAmphoursUsed = hour * averageCurrent;
    totalAmphoursUsed_ = totalAmphoursUsed_ + currentAmphoursUsed;
}
