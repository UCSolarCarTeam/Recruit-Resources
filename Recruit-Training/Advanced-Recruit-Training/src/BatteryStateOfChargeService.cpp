#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

#define HOURS_TO_MS 3600000.0

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent),
  initialAmpHours_( BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent/100)),
  totalAmpHoursUsed_(BATTERY_AMP_HOUR_CAPACITY - initialAmpHours_),
  prevTime_(QTime(0,0))
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{ 
    return totalAmpHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return current_ < 0;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeUntilChargedOrDepleted;

    if(isCharging())
    {
        double hoursUntilCharged = -1 * totalAmpHoursUsed_ / current_;
        timeUntilChargedOrDepleted = hoursUntilCharged;
    } else
    {
        double hoursUntilDepleted = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / current_;
        timeUntilChargedOrDepleted = hoursUntilDepleted;
    }

    QTime time = QTime(0,0);
    time = time.addMSecs(timeUntilChargedOrDepleted * HOURS_TO_MS);
    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    prevCurrent_ = current_;
    current_ = batteryData.current;
    voltage_ = batteryData.voltage;

    prevTime_ = currentTime_;
    currentTime_ = batteryData.time;

    double averageCurrent = ((prevCurrent_ + current_)/2);
    double hours = (prevTime_.msecsTo(currentTime_)) / HOURS_TO_MS;
    totalAmpHoursUsed_ +=  averageCurrent * hours;
}
