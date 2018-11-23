#include "BatteryStateOfChargeService.h"

#include <QDebug>
#include <cmath>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int    HOURS_TO_MS               = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent / 100);
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
    double hoursUntilComplete, milliUntilComplete;

    if(isCharging())
        hoursUntilComplete = totalAmpHoursUsed() / -latestCurrent_;
    else
        hoursUntilComplete = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / latestCurrent_;

    milliUntilComplete = hoursUntilComplete * HOURS_TO_MS;

    return QTime(0, 0, 0, 0).addMSecs(static_cast<int>(milliUntilComplete));
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if(containsData_)
    {
        double averageCurrent = (latestCurrent_ + batteryData.current) / 2,
               milliSinceLastData = latestTime_.msecsTo(batteryData.time),
               hoursSinceLastData = milliSinceLastData / static_cast<double>(HOURS_TO_MS);

        ampHoursUsed_ += averageCurrent * hoursSinceLastData;
    }
    else
        containsData_ = true;

    latestCurrent_ = batteryData.current;
    latestTime_ = batteryData.time;
}
