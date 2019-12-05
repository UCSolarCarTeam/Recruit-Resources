#include "BatteryStateOfChargeService.h"
#include <cmath>

namespace
{
const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
const int HOURS_TO_MILISECONDS = 3600000;
const int MINUTES_TO_MILISECONDS = 60000;
const int SECONDS_TO_MILISECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
{
    amphour_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
    current_ = 0;
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
    return hoursInteger_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    double currentOld_ = current_;
    current_ = batteryData.current;

    QTime timeOld = time_;
    time_ = batteryData.time;

    double averageAmphour_ = (current_ + currentOld_) / 2;

    //timeOld_ would be null for the first entry of data
    if (!timeOld.isNull())
    {
        amphour_ += averageAmphour_ * timeOld.msecsTo(time_) / HOURS_TO_MILISECONDS;
    }

    double totalTimeHoursDouble;
    //Calculation of the time until charged/depleted
    if (isCharging())
    {
        totalTimeHoursDouble =  abs(amphour_ / current_);
    }
    else
    {
        totalTimeHoursDouble =  (BATTERY_AMP_HOUR_CAPACITY - amphour_) / current_;
    }

    //Calculating the Time
    miliseconds_ = totalTimeHoursDouble * HOURS_TO_MILISECONDS;
    hoursInteger_ = floor(totalTimeHoursDouble);
    miliseconds_ = miliseconds_ - (hoursInteger_ * HOURS_TO_MILISECONDS);
    minutes_ = floor(miliseconds_ / MINUTES_TO_MILISECONDS);
    miliseconds_ = miliseconds_ - (minutes_ * MINUTES_TO_MILISECONDS);
    seconds_ = floor(miliseconds_ / SECONDS_TO_MILISECONDS);
    miliseconds_ = miliseconds_ - (seconds_ * SECONDS_TO_MILISECONDS);
    miliseconds_ = floor(miliseconds_);
}
