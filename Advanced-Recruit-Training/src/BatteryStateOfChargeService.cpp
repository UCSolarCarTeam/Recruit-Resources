#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_MILLISECONDS = 36000000.0;

}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHrUsed = BATTERY_AMP_HOUR_CAPACITY - ( BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent /100));

}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return AmpHrUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(current_t > 0)
        return true;
    else
        return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime time(0,0,0,0);
    int time_left;
    if(isCharging()){
        time_left = (totalAmpHoursUsed()/ current_t) * HOUR_TO_MILLISECONDS;
    }
    else
    {
        time_left = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_t) * HOUR_TO_MILLISECONDS;
    }

    return time.addMSecs(time_left);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);

    current_t = batteryData.current;
    voltage_t = batteryData.voltage;
    time_t = batteryData.time;

    prevCurr = current_t;
    prevTime = time_t;

    double avgCurr = (prevCurr + current_t) / 2 ;
    double DeltaTime = time_t.msecsTo(prevTime) / HOUR_TO_MILLISECONDS;

    AmpHrUsed += avgCurr* DeltaTime;
}
