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
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (currentNow_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   double hoursTillChargedOrDepleted, msTillChargedorDepleted;
   int hours, minutes, seconds, miliseconds;

   if (isCharging())
        hoursTillChargedOrDepleted = abs(totalAmpHoursUsed_ / currentNow_);
   else
        hoursTillChargedOrDepleted = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / currentNow_;

   while (hoursTillChargedOrDepleted > 24)
        hoursTillChargedOrDepleted -= 24;

   msTillChargedorDepleted = hoursTillChargedOrDepleted * MS_IN_HOURS;

   hours = floor(hoursTillChargedOrDepleted);
   msTillChargedorDepleted -= hours * MS_IN_HOURS;

   minutes = floor(msTillChargedorDepleted / MS_IN_MINUTES);
   msTillChargedorDepleted -= minutes * MS_IN_MINUTES;

   seconds = floor(msTillChargedorDepleted / MS_IN_SECONDS);
   msTillChargedorDepleted -= seconds * MS_IN_SECONDS;

   miliseconds = floor(msTillChargedorDepleted);

   QTime timeRemaining(hours, minutes, seconds, miliseconds);
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
}
