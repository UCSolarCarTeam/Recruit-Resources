#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTextStream>
#include <cmath>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double CONVERT_MS_TO_HR = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), current_(0.0), voltage_(0.0),
time_(QTime(0,0,0,0)), lastCurrent_(0.0), lastTime_(QTime(0,0,0,0)), firstRun_(true),
currentAmpHourUsed_((initialStateOfChargePercent_/100.0) * BATTERY_AMP_HOUR_CAPACITY)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return currentAmpHourUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
  return current_ < 0 ? true : false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   double remainingHours;
   if (isCharging())
   {
      remainingHours = currentAmpHourUsed_/current_;
   }
   else
   {
      remainingHours = (BATTERY_AMP_HOUR_CAPACITY - currentAmpHourUsed_)/current_;
   }

   if (remainingHours < 0)
   {
      remainingHours = remainingHours * -1;
   }

  if (remainingHours > 24) //get rid of multiplication factor
  {
    remainingHours = fmod(remainingHours, 24.0);
  }

   int hours = int(remainingHours);
   double actual_minutes = (remainingHours - hours) * 60.0;
   int minute = int(actual_minutes);
   double actual_seconds = (actual_minutes - minute) * 60.00;
   int seconds = int(actual_seconds) ;
   int ms = int((actual_seconds - seconds) * 1000.0);

   return  QTime(hours, minute, seconds, ms);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.   

    if (firstRun_)
    {
        firstRun_ = false;
        lastTime_ = batteryData.time_;
        lastCurrent_ = batteryData.current_;
    }
    else
    {
      lastTime_ = time_;
      lastCurrent_ = current_;

      double changeInAmpHours = ((batteryData.current_ + lastCurrent_)/2.0) * (lastTime_.msecsTo(batteryData.time_)/CONVERT_MS_TO_HR);
      currentAmpHourUsed_ = currentAmpHourUsed_ + changeInAmpHours;
    }
    current_ = batteryData.current_;
    voltage_ = batteryData.voltage_;
    time_ = batteryData.time_;
}
