#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QDebug>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_MILLISECONDS = 36000000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY - ((initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY);
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
    if(current_ > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   QTime time(0,0,0,0);
   int timeLeft;
   if(isCharging())
   {
       timeLeft = (totalAmpHoursUsed() / current_) * HOUR_TO_MILLISECONDS;
   }
   else
   {
       timeLeft = ((BATTERY_AMP_HOUR_CAPACITY  - totalAmpHoursUsed()) / current_) * HOUR_TO_MILLISECONDS;
   }
   return time.addMSecs(timeLeft);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    previousCurrent_ = current_;
    previousTime_ = time_;
    current_ = batteryData.current;
    voltage_ = batteryData.voltage;
    time_ = batteryData.time;
    averageCurrent_ = (previousCurrent_ + current_) / 2;
    changeInTime_ = time_.msecsTo(previousTime_) / HOUR_TO_MILLISECONDS;
    ampHoursUsed_ += averageCurrent_ * changeInTime_;
}
