#include "BatteryStateOfChargeService.h"
#include <QTextStream>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOURS_TO_MILISECONDS = 3600000;
    const int HOURS_TO_MINUTES = 60;
    const int MINUTES_TO_SECONDS = 60;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
{
    amphour_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
    currentNew_ = 0;
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
    return (currentNew_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    int hours;
    int minutes;
    int seconds;
    int overlapsHours;
    double totalTimeHours;

    if (isCharging())
    {
        totalTimeHours =  abs(amphour_ / currentNew_);
    }
    else
    {
        totalTimeHours =  (BATTERY_AMP_HOUR_CAPACITY - amphour_) / currentNew_;
    }

    //Rounding the total time (in hours) down
    hours = totalTimeHours;
    //Minute is whatever left over multiply by 60 (hours to minute)
    minutes = (totalTimeHours - hours) * HOURS_TO_MINUTES;
    seconds = (totalTimeHours * HOURS_TO_MINUTES - hours* HOURS_TO_MINUTES - minutes) * MINUTES_TO_SECONDS;
    overlapsHours = (hours / 24) * 24;
    hours -= overlapsHours;
    return QTime(hours, minutes, seconds, overlapsHours);
}

//Use "one time use" variable as a local variable
void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData)
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    double currentOld_ = currentNew_;
    currentNew_ = batteryData.current;

    QTime timeOld_ = timeNew_;
    timeNew_ = batteryData.time;

    double averageAmphour_ = (currentNew_ + currentOld_) / 2;
    if (!timeOld_.isNull())
    {
        amphour_ += averageAmphour_ * timeOld_.msecsTo(timeNew_)/HOURS_TO_MILISECONDS;
    }
}
