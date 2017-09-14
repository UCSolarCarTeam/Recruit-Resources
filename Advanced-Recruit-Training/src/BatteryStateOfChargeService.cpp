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
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY - ((initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY);
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
    int timeRemaining_;
    if (isCharging())
    {
       timeRemaining_ = (totalAmpHoursUsed() / current_) * HOUR_IN_MSECONDS;
    }
    else
    {
       timeRemaining_ = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_) * HOUR_IN_MSECONDS;
    }
    QTime time (0,0,0,0);
    return time.addMSecs(timeRemaining_);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    previousTime_ = time_;
    previousCurrent_ = current_;
    voltage_ = batteryData.voltage;
    current_ = batteryData.current;
    time_ = batteryData.time;
    averageCurrent_ = ((current_ + previousCurrent_)/2);
    changeInTime_ = time_.msecsTo(previousTime_) / HOUR_IN_MSECONDS;
    ampHoursUsed_ += averageCurrent_ * changeInTime_;
}
