#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MSEC_TO_HR = 1 / 1000 / 3600;
    const double HR_TO_MSEC = 1000 * 3600;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, remainingAmphours_(BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent / 100)
{ 
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - remainingAmphours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (lastDataPoint_.current < 0) ? true : false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime ret(0, 0, 0, 0);
    if (isCharging()) {
        return ret.addMSecs(totalAmpHoursUsed() / qAbs(lastDataPoint_.current) * HR_TO_MSEC);
    } else {
        return ret.addMSecs(remainingAmphours_ / lastDataPoint_.current * HR_TO_MSEC);
    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    int msecs = lastDataPoint_.time.msecsTo(batteryData.time);
    double avgAmps = (batteryData.current + lastDataPoint_.current) / 2;
    remainingAmphours_ -= (double) msecs * MSEC_TO_HR * avgAmps;

    lastDataPoint_.time = batteryData.time;
    lastDataPoint_.voltage = batteryData.voltage;
    lastDataPoint_.current = batteryData.current;
}
