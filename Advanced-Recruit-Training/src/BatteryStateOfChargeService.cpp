#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_IN_HOUR = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, previousCurrent_(0)
, ampHoursUsed_ (BATTERY_AMP_HOUR_CAPACITY * (1 - (initialStateOfChargePercent_ / 100)))
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
{
    if (previousCurrent_ < 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double hours;
    QTime timeToChargeOrDepletion(0,0,0,0);

    if (isCharging())
    {
        hours = ampHoursUsed_ / qAbs(previousCurrent_);
    }
    else
    {
        hours = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_) / previousCurrent_;
    }

    timeToChargeOrDepletion = timeToChargeOrDepletion.addMSecs(hours * MILLISECONDS_IN_HOUR);
    return timeToChargeOrDepletion;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double timeDifference = 0;

    if (isFirstRecord_)
    {
        isFirstRecord_ = false;
    }
    else
    {
        timeDifference = (double)previousTime_.msecsTo(batteryData.time) / MILLISECONDS_IN_HOUR;
    }

    ampHoursUsed_ += ((previousCurrent_ + batteryData.current) / 2) * timeDifference;

    previousTime_ = batteryData.time;
    previousCurrent_ = batteryData.current;
}
