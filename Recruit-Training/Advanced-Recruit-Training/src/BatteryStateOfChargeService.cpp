#include "BatteryStateOfChargeService.h"

#include <QDebug>
#include <cmath>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int    HOURS_TO_MS               = 3600000;
    const int    HOURS_IN_DAY              = 24;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = 0.0;
    containsData_ = false;
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
    return latestCurrent_ < 0.0;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double temp;                                    // Stores temporary values of the total part of the time (i.e. 3600 seconds)

    // Store temp as hours
    if(isCharging())
        // Time Until Charged = Amphours Used (Ah) / Average Current (A)
        temp = totalAmpHoursUsed() / -latestCurrent_;
    else
        // Time Until Depleted = (Amphour Capacity (Ah) - Amphours Used (Ah)) / Average Current (A)
        temp = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / latestCurrent_;

    temp = fmod(temp, HOURS_IN_DAY) * HOURS_TO_MS;

    return QTime(0, 0, 0, 0).addMSecs(static_cast<int>(temp));
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if(!containsData_) {
        // Set the initial amphours used (battery's Amphour capacity (Ah) * state of charge (%))
        ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_ / 100);
        containsData_ = true;
    } else
        // Add the change in amphours (average current (A) * difference in time (h))
        ampHoursUsed_ += (latestCurrent_ + batteryData.current)/2 * (latestTime_.msecsTo(batteryData.time) / static_cast<double>(HOURS_TO_MS));


    latestCurrent_ = batteryData.current;
    latestTime_ = batteryData.time;
}
