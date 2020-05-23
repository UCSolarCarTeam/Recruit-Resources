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
: initialStateOfChargePercent_(initialStateOfChargePercent), TimeWhenChargedOrDepleted_(1,1,1,1), OldCurrent_(0), PresentBatteryCurrent_(0), TotalAmpHoursUsed_(0), IsCharging_(0)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return TotalAmpHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return IsCharging_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   return TimeWhenChargedOrDepleted_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    OldCurrent_= PresentBatteryCurrent_;
    PresentBatteryCurrent_= batteryData.current;
    OldTime_= PresentTime_;
    PresentTime_= batteryData.time;

    //total AmpHours Used

    double initial_amountof_amphours_used= (BATTERY_AMP_HOUR_CAPACITY* initialStateOfChargePercent_)/100;
    double average_current= (PresentBatteryCurrent_+ OldCurrent_)/2;

    if (OldTime_.isValid())
    {
        double time_difference_in_hours= OldTime_.msecsTo(PresentTime_)/3600000.0;
        TotalAmpHoursUsed_+= average_current* time_difference_in_hours;
    }
        else
        {
        TotalAmpHoursUsed_= initial_amountof_amphours_used;
        }

    //isCharging

    if (PresentBatteryCurrent_> 0)
    {
        IsCharging_= false;
    }
        else if (PresentBatteryCurrent_< 0)
        {
         IsCharging_= true;
        }

    //Time of Charging or Depletions

    double TimeInHours_;
    int Hours_;
    int Minutes_;
    int Seconds_;
    int Milliseconds_;

    if(isCharging())
     {
        TimeInHours_= abs(totalAmpHoursUsed()/PresentBatteryCurrent_);
     }
        else
        {
         TimeInHours_= (BATTERY_AMP_HOUR_CAPACITY-totalAmpHoursUsed())/PresentBatteryCurrent_;
        }

    while (TimeInHours_> 24)
    {
         TimeInHours_-= 24;
    }

     Hours_= (int)(TimeInHours_);

     double RemainingFractionaMinutes_= (TimeInHours_- Hours_)* 60;
     Minutes_= (int)(RemainingFractionaMinutes_);

     double RemainingFractionalSeconds_= (RemainingFractionaMinutes_- Minutes_)* 60;
     Seconds_= (int)(RemainingFractionalSeconds_);

     double RemainingFractionalMilliseconds_= (RemainingFractionalSeconds_- Seconds_)* 1000;
     Milliseconds_= (int)(RemainingFractionalMilliseconds_);

     QTime N_ (Hours_, Minutes_, Seconds_, Milliseconds_);
     TimeWhenChargedOrDepleted_= N_;
}
