#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MS_IN_HOUR = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
}

// Empty since children will be destroyed
BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (dataPoint_.current < 0) {
       return true;
    }
    return false;
}

// Amphours used divided by current or remaining amphours divided by current
QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double hoursTillChargedOrDepleted;
    QTime msDuration(0,0,0,0);

    if (isCharging()) {
        hoursTillChargedOrDepleted = ampHoursUsed_ / dataPoint_.current * -1;
    } else {
        hoursTillChargedOrDepleted = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_) / dataPoint_.current;
    }

    msDuration = msDuration.addMSecs(hoursTillChargedOrDepleted * MS_IN_HOUR);
    return msDuration;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    double averageCurrent = (dataPoint_.current + batteryData.current) / 2;
    double timeDifferenceHours = (double) dataPoint_.time.msecsTo(batteryData.time) / MS_IN_HOUR;
    ampHoursUsed_ += averageCurrent * timeDifferenceHours;

    dataPoint_ = batteryData;
}
