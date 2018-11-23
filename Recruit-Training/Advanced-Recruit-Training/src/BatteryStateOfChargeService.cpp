#include "BatteryStateOfChargeService.h"
#include <QTextStream>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    last_current = 0.0;
    last_time = QTime(0,0,0,0);

    current = 0.0;
    voltage = 0.0;
    time = QTime(0,0,0,0);

    currentAmpHourUsed = 0; //(initialStateOfChargePercent/100.0) * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return currentAmpHourUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (current < 0)
        return true;
    else
        return false;

}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   double remainingHours;
   if (isCharging())
       remainingHours = currentAmpHourUsed/current;
   else
       remainingHours = (BATTERY_AMP_HOUR_CAPACITY - currentAmpHourUsed)/current;

   if (remainingHours < 0)
          remainingHours = remainingHours * -1;

   while (remainingHours > 24) //get rid of multiplication factor
       remainingHours = remainingHours - 24.0;

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
    //Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    if (currentAmpHourUsed == 0.0)
    {
        last_time = batteryData.time;
        last_current = batteryData.current;

        current = batteryData.current;
        voltage = batteryData.voltage;
        time = batteryData.time;

        currentAmpHourUsed = (initialStateOfChargePercent_/100.0) * BATTERY_AMP_HOUR_CAPACITY;
    }
      else
      {
        last_time = time;
        last_current = current;

        current = batteryData.current;
        voltage = batteryData.voltage;
        time = batteryData.time;

        double changeInAmpHours = ((current + last_current)/2.0) * (last_time.msecsTo(time)/(60.0*60.0*1000.0));

        currentAmpHourUsed = currentAmpHourUsed + changeInAmpHours;
        }

}
