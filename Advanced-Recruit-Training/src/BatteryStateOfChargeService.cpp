#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent;
}

// Empty since children will be destroyed
BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_;
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

    hoursTillChargedOrDepleted = ampHoursUsed_ / dataPoint_.current;
    if (isCharging()) {
       hoursTillChargedOrDepleted *= -1;
    }

    QTime msDuration;
    msDuration.addMSecs(hoursTillChargedOrDepleted * 3600000);
    return msDuration;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    double averageCurrent = dataPoint_.current + batteryData.current / 2;
    double timeDifferenceHours = dataPoint_.time.msecsTo(batteryData.time) / 3600000;
    ampHoursUsed_ = averageCurrent * timeDifferenceHours;

    dataPoint = batteryData;
}
