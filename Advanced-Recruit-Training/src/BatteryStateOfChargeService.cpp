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
    return 0.0;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (amperage_ < 0) {
       return true;
    }
    return false;
}

# Amphours used divided by current or remaining amphours divided by current
QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    // TODO: Check if it is charging and then calculate value
    double hoursTillChargeOrDepleted;
    if (isCharging()) {
       hoursTillChargeOrDepleted = ampHoursUsed_ / amperage_;
    } else {
       hoursTillChargeOrDepleted = ampHoursUsed_ / amperage * -1;
    }
    time_ += hoursTillChargeOrDepleted;
    return time_
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    amperage_ = batteryData.current;

}
