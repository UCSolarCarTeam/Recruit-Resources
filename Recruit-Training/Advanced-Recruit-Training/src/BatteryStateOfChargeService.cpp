#include <math.h>
#include <QTime>

#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int MS_IN_HOURS = 3600000;
    const int MS_IN_MINUTES = 60000;
    const int MS_IN_SECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    /*
                : initialStateOfChargePercent_(initialStateOfChargePercent)
      Same as ^   initialStateOfChargePercent_ = initialStateOfChargePercent;
      Another example in BatteryData.cpp                                     */
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

/*Returns the total amp hours used*/
double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHoursUsed_;
}

/* The battery is charging if the battery current is negative
 * The battery is depleting if the battery current is positive
 * Returns true if the battery is being charged, false if not.*/
bool BatteryStateOfChargeService::isCharging() const
{
    if (currentNow_ < 0)
    {
        return true;
    } else
    {
        return false;
    }
}

/* Amphours used (Ah) divided by the current (A) is the time until charged
 * Remaining Amphours (Ah) divided by the current (A) is the time until depletion
 * Return the time remaining to when the battery is charged or depleted*/
QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   double hoursTillChargedOrDepleted, msTillChargedorDepleted;
   int h, m, s, ms;

   if (isCharging())
   {
      hoursTillChargedOrDepleted = abs(totalAmpHoursUsed_ / currentNow_);

   } else
   {
      hoursTillChargedOrDepleted = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / currentNow_;
   }

   while (hoursTillChargedOrDepleted > 24)
       hoursTillChargedOrDepleted -= 24;

   msTillChargedorDepleted = hoursTillChargedOrDepleted * MS_IN_HOURS;

   h = floor(hoursTillChargedOrDepleted);
   msTillChargedorDepleted -= h * MS_IN_HOURS;

   m = floor(msTillChargedorDepleted / MS_IN_MINUTES);
   msTillChargedorDepleted -= m * MS_IN_MINUTES;

   s = floor(msTillChargedorDepleted / MS_IN_SECONDS);
   msTillChargedorDepleted-= s * MS_IN_SECONDS;

   ms = floor(msTillChargedorDepleted);

   QTime timeRemaining(h, m, s, ms);
   return timeRemaining;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    initialAmpHoursUsed_ = (initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY;

    currentOld_ = currentNow_;
    currentNow_ = batteryData.current;
    currentAverage_ = (currentOld_ + currentNow_) / 2;

    timeOld_ = timeNow_;
    timeNow_ = batteryData.time;

    if (timeOld_.isValid())
    {
        timeDiffMSec_ = timeOld_.msecsTo(timeNow_);
        totalAmpHoursUsed_ += currentAverage_ * timeDiffMSec_ / MS_IN_HOURS;
    } else
    {
        totalAmpHoursUsed_ = initialAmpHoursUsed_;
    }

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
