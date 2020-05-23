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
: initialStateOfChargePercent_(initialStateOfChargePercent), timeWhenChargedOrDepleted_(1,1,1,1), oldCurrent_(0), presentBatteryCurrent_(0), totalAmpHoursUsed_(0), isCharging_(0)
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
    oldCurrent_= presentBatteryCurrent_;
    presentBatteryCurrent_= batteryData.current;
    oldTime_= presentTime_;
    presentTime_= batteryData.time;

    double initialAmountOfAmphoursUsed_= (BATTERY_AMP_HOUR_CAPACITY* initialStateOfChargePercent_)/100;
    double averageCurrent_= (presentBatteryCurrent_+ oldCurrent_)/2;

    if (oldTime_.isValid())
    {
        double timeDifferenceInHours_= oldTime_.msecsTo(presentTime_)/3600000.0;
        totalAmpHoursUsed_+= averageCurrent_* timeDifferenceInHours_;
    }
    else
    {
        totalAmpHoursUsed_= initialAmountOfAmphoursUsed_;
    }

    if (presentBatteryCurrent_> 0)
    {
        isCharging_= false;
    }
    else if (presentBatteryCurrent_< 0)
    {
         isCharging_= true;
    }

    double timeInHours_;
    int hours_;
    int minutes_;
    int seconds_;
    int milliseconds_;

    if(isCharging())
     {
        timeInHours_= abs(totalAmpHoursUsed()/presentBatteryCurrent_);
     }
     else
     {
         timeInHours_= (BATTERY_AMP_HOUR_CAPACITY-totalAmpHoursUsed())/presentBatteryCurrent_;
     }

    while (timeInHours_> 24)
    {
         timeInHours_-= 24;
    }

     hours_= (int)(timeInHours_);

     double remainingFractionaMinutes_= (timeInHours_- hours_)* 60;
     minutes_= (int)(remainingFractionaMinutes_);

     double remainingFractionalSeconds_= (remainingFractionaMinutes_- minutes_)* 60;
     seconds_= (int)(remainingFractionalSeconds_);

     double remainingFractionalMilliseconds_= (remainingFractionalSeconds_- seconds_)* 1000;
     milliseconds_= (int)(remainingFractionalMilliseconds_);

     QTime n_ (hours_, minutes_, seconds_, milliseconds_);
     timeWhenChargedOrDepleted_= n_;
}
