#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOURS_TO_MILISECONDS = 3600000;
    const int HOURS_TO_MINUTES = 60;
    const int MINUTES_TO_SECONDS = 60;
    const int SECONDS_TO_MILISECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
{
    amphour_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
    current_ = 0;
    totalHours_ = 0;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return amphour_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (current_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return QTime(0, minutes_, seconds_, miliseconds_);
}

int BatteryStateOfChargeService::getHours() const
{
    return hours_;
}


void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    double currentOld_ = current_;
    current_ = batteryData.current;

    QTime timeOld_ = time;
    time = batteryData.time;

    double averageAmphour_ = (current_ + currentOld_) / 2;

    //timeOld_ would be null for the first entry of data
    if (!timeOld_.isNull())
    {
        amphour_ += averageAmphour_ * timeOld_.msecsTo(time) / HOURS_TO_MILISECONDS;
    }

    //Calculation of the time until charged/depleted
    if (isCharging())
    {
        totalTimeHours_ =  abs(amphour_ / current_);
    }
    else
    {
        totalTimeHours_ =  (BATTERY_AMP_HOUR_CAPACITY - amphour_) / current_;
    }

    //Rounding the total time (in hours) down
    hours_ = totalTimeHours_;
    //Minute is whatever left over multiply by 60 (hours to minute)
    minutes_ = (totalTimeHours_ - hours_) * HOURS_TO_MINUTES;
    seconds_ = ((totalTimeHours_ - hours_) * HOURS_TO_MINUTES - minutes_) * MINUTES_TO_SECONDS;
    miliseconds_ = (((totalTimeHours_ - hours_) * HOURS_TO_MINUTES - minutes_) * MINUTES_TO_SECONDS - seconds_) * SECONDS_TO_MILISECONDS;
}
