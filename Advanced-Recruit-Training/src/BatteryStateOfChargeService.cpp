#include <QDebug>

#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent),
  remainingAmphours_(BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent / 100)
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
    return (lastPoint.current < 0) ? true : false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime ret(0, 0, 0, 0);
    return ret.addMSecs(((isCharging()) ? totalAmpHoursUsed() : remainingAmphours_) / qAbs(lastPoint.current) * 3600 * 1000);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    int msecs = lastPoint.time.msecsTo(batteryData.time);
    double avgAmps = (batteryData.current + lastPoint.current) / 2;
    remainingAmphours_ -= (double) msecs / 1000 / 3600 * avgAmps;
    lastPoint.time = batteryData.time;
    lastPoint.voltage = batteryData.voltage;
    lastPoint.current = batteryData.current;
}
