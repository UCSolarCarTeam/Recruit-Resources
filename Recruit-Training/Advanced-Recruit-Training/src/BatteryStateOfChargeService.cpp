#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <math.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int SECONDS_TO_HOURS = 3600;
    const int PERCENT_TO_DECIMAL = 100;
    const int MILLISECONDS_IN_HOUR = 3600000;
    const int MILLISECONDS_IN_MINUTE = 60000;
    const int MILLISECONDS_IN_SECOND = 1000;
    const int HOURS_IN_A_DAY  = 24;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
    , ampHours_(BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / PERCENT_TO_DECIMAL)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (current_ < 0);
}

int BatteryStateOfChargeService::getRemainingHours() const
{
    return remainingHours_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return timeTillChargeOrDepletion_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    QTime timeOld = time_;
    double currentOld = current_;

    current_ = batteryData.current;
    time_ = batteryData.time;

    if(!timeOld.isNull())
    {
        double avgCurrent = (currentOld + current_) / 2;
        ampHours_ += (avgCurrent * timeOld.secsTo(time_) / SECONDS_TO_HOURS);
    }

    //calculate remaining time for charge or depletion
    double totalHours;

    if(isCharging())
    {
        totalHours = qAbs(totalAmpHoursUsed() / current_);
    }
    else
    {
        totalHours = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_;
    }

    int milliseconds = totalHours * MILLISECONDS_IN_HOUR;

    int hours = floor(totalHours);
    milliseconds -= hours * MILLISECONDS_IN_HOUR;

    int minutes = floor(milliseconds / MILLISECONDS_IN_MINUTE);
    milliseconds -= minutes * MILLISECONDS_IN_MINUTE;

    int seconds = floor(milliseconds / MILLISECONDS_IN_SECOND);
    milliseconds -= seconds * MILLISECONDS_IN_SECOND;

    if((hours - HOURS_IN_A_DAY) >= 0) // if 24 hours or more
    {
        remainingHours_ = hours - (HOURS_IN_A_DAY - 1); // calculate the amount of hours needed to take out of "hours" as "hours" can only hold up to 23
    }
    else
    {
        remainingHours_ = 0;
    }

    hours -= remainingHours_;

    timeTillChargeOrDepletion_.setHMS(hours, minutes, seconds, milliseconds);
}
