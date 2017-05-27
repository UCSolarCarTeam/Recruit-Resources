#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QDebug>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOUR_IN_MILLISECONDS = 36000000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY - (initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{

}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return AmpHoursUsed_;
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

   if(current_ < 0)
   {
       timeLeft = (totalAmpHoursUsed() / current_) * HOUR_IN_MILLISECONDS;
   }
   else
   {
       timeLeft = ((BATTERY_AMP_HOUR_CAPACITY  - totalAmpHoursUsed())/current_) * HOUR_IN_MILLISECONDS;
   }

   return time.addMSecs(timeLeft);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    previouscurrent_ = current_;
    previoustime_ = time_;
    current_ = batteryData.current;
    voltage_ = batteryData.voltage;
    time_ = batteryData.time.toString("hhmm.ss").toDouble();
    AmpHoursUsed_ += ((previouscurrent_ + current_) / 2) * (previoustime_ - time_);
}
