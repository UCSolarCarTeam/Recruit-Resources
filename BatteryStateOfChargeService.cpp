#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHourUsed_ = 0.0;
    timeTilCharged_ = QTime (0,0,0,0);
    timeTilDepleted_ = QTime (0,0,0,0);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHourUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return isCharging_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   if(isCharging_)
   {
      return timeTilCharged_;
   }

   else
   {
      return timeTilDepleted_;
   }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    const double MILLISECONDS_TO_HOURS = 1/3600000.0;
    const double PERCENT_TO_DECIMAL = 0.01;
        if(ampHourUsed_ == 0.0)
        {
             ampHourUsed_ = BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_*PERCENT_TO_DECIMAL;
        }
        else
        {
             ampHourUsed_ += ((previousCurrent_+batteryData.current)/2)*((previousTime_).msecsTo(batteryData.time)*MILLISECONDS_TO_HOURS);
        }

    if(batteryData.current >= 0)
    {
        isCharging_ = false;
    }
    else
    {
        isCharging_ = true;
    }

    previousCurrent_ = batteryData.current;
    previousTime_ = batteryData.time;
    hourCharge_ = ampHourUsed_/batteryData.current;
    if(hourCharge_<0)
    {
        hourCharge_ *= -1;
    }
    hourUsed_ = (BATTERY_AMP_HOUR_CAPACITY-ampHourUsed_)/batteryData.current;
    QTime hourTilCharged = QTime (0,0,0,0);
    QTime hourTilDepleted = QTime (0,0,0,0);
    hourTilCharged = hourTilCharged.addMSecs((int)(hourCharge_/MILLISECONDS_TO_HOURS));
    hourTilDepleted = hourTilDepleted.addMSecs((int)(hourUsed_/MILLISECONDS_TO_HOURS));
    timeTilCharged_ = hourTilCharged;
    timeTilDepleted_ = hourTilDepleted;
}
