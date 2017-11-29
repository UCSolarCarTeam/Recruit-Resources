#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MS_PER_HOUR = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), currentCurrent_(0),
  ampHoursUsed_(BATTERY_AMP_HOUR_CAPACITY * (1 - (initialStateOfChargePercent_ / 100)))
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
// returns true if current is negative
{
    if (currentCurrent_ < 0)
    {
        return true;
    }

    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
// calculates time (in hours) and returns it in QTime
{
    double hours;
    if (isCharging())
    {
        hours = ampHoursUsed_ / qAbs(currentCurrent_);
    }
    else
    {
        hours = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_) / currentCurrent_;
    }

    QTime nullTime(0, 0);
    QTime clockTime = nullTime.addMSecs(hours * MS_PER_HOUR);
    return clockTime;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
// update ampHoursUsed, time and current
{
    double previousCurrent = currentCurrent_;
    currentCurrent_ = batteryData.current;

    QTime previousTime = currentTime_;
    currentTime_ = batteryData.time;

    double timeDiff;
    if (!currentTime_.isValid())
    {
        timeDiff = 0;
    }
    else
    {
        // calculates difference between previous time and current time in ms
        // divide by MS_PER_HOUR to get difference in hours
        timeDiff = (double)previousTime.msecsTo(currentTime_) / MS_PER_HOUR;
    }

    ampHoursUsed_ += ((previousCurrent + currentCurrent_) / 2) * timeDiff;
}
