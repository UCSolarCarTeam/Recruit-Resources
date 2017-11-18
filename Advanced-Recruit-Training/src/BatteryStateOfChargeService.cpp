#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    current_ = 0;
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY - BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
    time_.setHMS(0,0,0,0);
    chargeTime_.setHMS(0,0,0,0);
    numberOfRecords_ = 0;
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
    if (current_ < 0 )
        return true;
    else
        return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return chargeTime_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double timeDifference;
    double hours;
    chargeTime_.setHMS(0,0,0,0);

    if (numberOfRecords_ > 0)
    {
        timeDifference = (double)time_.msecsTo(batteryData.time)/3600000;
    }
    numberOfRecords_++;

    ampHoursUsed_ += ((current_ + batteryData.current)/2)*timeDifference;

    time_ = batteryData.time;
    current_ = batteryData.current;

    if (isCharging())
         hours = -ampHoursUsed_/current_;
    else
        hours = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_)/current_;

    chargeTime_ = chargeTime_.addMSecs(hours*3600000);
}
