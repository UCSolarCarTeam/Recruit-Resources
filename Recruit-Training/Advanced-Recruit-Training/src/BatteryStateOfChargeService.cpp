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
: initialStateOfChargePercent_(initialStateOfChargePercent), currentNow_(0),
  totalAmpHoursUsed_(0), timeRemaining_(1, 1, 1)
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
   return timeRemaining_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double initialAmpHoursUsed = (initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY;

    double currentOld = currentNow_;
    currentNow_ = batteryData.current;
    double currentAverage = (currentOld + currentNow_) / 2;

    QTime timeOld = timeNow_;
    timeNow_ = batteryData.time;

    if (timeOld.isValid())
    {
        double timeDiffMSec = timeOld.msecsTo(timeNow_);
        totalAmpHoursUsed_ += currentAverage * timeDiffMSec / MS_IN_HOURS;
    }
    else
    {
        totalAmpHoursUsed_ = initialAmpHoursUsed;
    }

    double hoursTillChargedOrDepleted;

    if (isCharging())
    {
         hoursTillChargedOrDepleted = abs(totalAmpHoursUsed_ / currentNow_);
    }
    else
    {
         hoursTillChargedOrDepleted = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / currentNow_;
    }

    while (hoursTillChargedOrDepleted > 24)
    {
         hoursTillChargedOrDepleted -= 24;
    }

    double msTillChargedorDepleted = hoursTillChargedOrDepleted * MS_IN_HOURS;

    int hours = floor(hoursTillChargedOrDepleted);
    msTillChargedorDepleted -= hours * MS_IN_HOURS;

    int minutes = floor(msTillChargedorDepleted / MS_IN_MINUTES);
    msTillChargedorDepleted -= minutes * MS_IN_MINUTES;

    int seconds = floor(msTillChargedorDepleted / MS_IN_SECONDS);
    msTillChargedorDepleted -= seconds * MS_IN_SECONDS;

    int milliseconds = floor(msTillChargedorDepleted);

    timeRemaining_.setHMS(hours, minutes, seconds, milliseconds);
}
