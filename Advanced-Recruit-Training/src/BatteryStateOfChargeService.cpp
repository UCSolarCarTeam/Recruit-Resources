#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MS_PER_HOUR = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), current_(0),
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
// returns true if current is positive
{
    if (current_ < 0)
    {
        return false;
    }

    return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
// calculates time (in hours) and returns it in QTime
{
    double time;
    if (isCharging())
    {
        time = ampHoursUsed_ / current_;
    }
    else
    {
        time = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_) / (current_ * -1);
    }

    QTime nullTime(0, 0);
    QTime clockTime = nullTime.addMSecs(time * MS_PER_HOUR);
    return clockTime;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
// update ampHoursUsed, time and current
{
    double timeDiff;
    if (!time_.isValid())
    {
        timeDiff = 0;
    }
    else
    {
        // calculates difference between previous time and current time in ms
        // divide by MS_PER_HOUR to get difference in hours
        timeDiff = (double)time_.msecsTo(batteryData.time) / MS_PER_HOUR;
    }

    ampHoursUsed_ += ((current_ + batteryData.current) / 2) * timeDiff;
    time_ = batteryData.time;
    current_ = batteryData.current;
}
