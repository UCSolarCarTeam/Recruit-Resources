#include "BatteryStateOfChargeService.h"

#include <QDebug>
#include <cmath>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = -404.0;
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

    temp = fmod(temp, 24) * 3600000;

    return QTime(0, 0, 0, 0).addMSecs(static_cast<int>(temp));
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Q_UNUSED(batteryData);

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    if(ampHoursUsed_ == -404.0)
        // Set the initial amphours used (battery's Amphour capacity (Ah) * state of charge (%))
        ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_ / 100);
    else
        // Add the change in amphours (average current (A) * difference in time (h))
        ampHoursUsed_ += (latestCurrent_ + batteryData.current)/2 * (latestTime_.msecsTo(batteryData.time) / 3600000.0);


    latestCurrent_ = batteryData.current;
    latestTime_ = batteryData.time;
}
