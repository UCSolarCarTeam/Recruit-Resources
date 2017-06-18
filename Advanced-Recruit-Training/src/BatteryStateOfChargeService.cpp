#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_IN_MSECONDS = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY - ((initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{

}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{ 
    return AmpHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if ( current_ >= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime time (0,0,0,0);
    int mseconds_;
    if (isCharging())
    {
       mseconds_ = (totalAmpHoursUsed() / current_) * HOUR_IN_MSECONDS;
    }
    else
    {
       mseconds_ = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_) * HOUR_IN_MSECONDS;
    }

    return time.addMSecs(mseconds_);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    previoustime_ = time_;
    previouscurrent_ = current_;
    voltage_ = batteryData.voltage;
    current_ = batteryData.current;
    time_ = batteryData.time;
    AmpHoursUsed_ += ((current_ + previouscurrent_)/2) * time_.msecsTo(previoustime_) / HOUR_IN_MSECONDS;
}
