#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>
#include <math.h>
#include <QTextStream>
#include <QString>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, timeWhenChargedOrDepleted_(1,1,1,1)
, presentBatteryCurrent_(0)
, totalAmpHoursUsed_(0)
, isCharging_(0)
, initialAmountOfAmphoursUsed_((BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_) / 100)
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
    return isCharging_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   return timeWhenChargedOrDepleted_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double oldCurrent = presentBatteryCurrent_;
    presentBatteryCurrent_ = batteryData.current;
    QTime oldTime = presentTime_;
    presentTime_ = batteryData.time;


    double averageCurrent = (presentBatteryCurrent_ + oldCurrent) / 2;

    if (oldTime.isValid())
    {
        double timeDifferenceInHours_ = oldTime.msecsTo(presentTime_) / 3600000.0;
        totalAmpHoursUsed_ += averageCurrent * timeDifferenceInHours_;
    }
    else
    {
        totalAmpHoursUsed_ = initialAmountOfAmphoursUsed_;
    }

    if (presentBatteryCurrent_ > 0)
    {
        isCharging_ = false;
    }
    else if (presentBatteryCurrent_ < 0)
    {
         isCharging_ = true;
    }

    double timeInHours;
    int hours;
    int minutes;
    int seconds;
    int milliseconds;

    if(isCharging())
     {
        timeInHours = abs(totalAmpHoursUsed() / presentBatteryCurrent_);
     }
     else
     {
         timeInHours = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / presentBatteryCurrent_;
     }

    while (timeInHours > 24)
    {
         timeInHours -= 24;
    }

     hours = (int)(timeInHours);

     double remainingFractionaMinutes = (timeInHours - hours) * 60;
     minutes = (int)(remainingFractionaMinutes);

     double remainingFractionalSeconds = (remainingFractionaMinutes - minutes) * 60;
     seconds = (int)(remainingFractionalSeconds);

     double remainingFractionalMilliseconds = (remainingFractionalSeconds - seconds) * 1000;
     milliseconds = (int)(remainingFractionalMilliseconds);

     QTime n (hours, minutes, seconds, milliseconds);
     timeWhenChargedOrDepleted_ = n;
}
