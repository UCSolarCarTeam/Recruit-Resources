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
    if (dataPoint_.current < 0)
    {
       return true;
    }
    return false;
}

// Amphours used divided by current or remaining amphours divided by current
QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double msDuration;
    QTime hoursTillChargedOrDepleted(0, 0, 0, 0);

    if (isCharging()) {
        msDuration = ampHoursUsed_ / qAbs(dataPoint_.current);
    } else {
        msDuration = (BATTERY_AMP_HOUR_CAPACITY - ampHoursUsed_) / dataPoint_.current;
    }

    hoursTillChargedOrDepleted = hoursTillChargedOrDepleted.addMSecs(msDuration * MS_IN_HOUR);
    return hoursTillChargedOrDepleted;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double averageCurrent = (dataPoint_.current + batteryData.current) / 2;
    double timeDifferenceHours = (double) dataPoint_.time.msecsTo(batteryData.time) / MS_IN_HOUR;
    ampHoursUsed_ += averageCurrent * timeDifferenceHours;

    dataPoint_ = batteryData;
}
