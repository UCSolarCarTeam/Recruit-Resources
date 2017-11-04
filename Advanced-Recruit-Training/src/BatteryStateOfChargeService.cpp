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
    ampHrUsed = BATTERY_AMP_HOUR_CAPACITY - (BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent / 100));

}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHrUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ > 0){
        return true;
    }
    else
    {
        return false;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime time(0,0,0,0);
    int time_left;
    if(isCharging()){
        time_left = (totalAmpHoursUsed()/ current_) * HOUR_TO_MILLISECONDS;
    }
    else
    {
        time_left = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_) * HOUR_TO_MILLISECONDS;
    }
    return time.addMSecs(time_left);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    current_ = batteryData.current;
    voltage_ = batteryData.voltage;
    time_ = batteryData.time;

    presentCurrent = current_;
    prevTime = time_;

    double avgCurr = (presentCurrent + current_) / 2.0;
    double deltaTime = time_.msecsTo(prevTime) / HOUR_TO_MILLISECONDS;

    ampHrUsed += avgCurr* deltaTime;
}
