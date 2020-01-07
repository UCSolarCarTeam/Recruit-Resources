#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_MILLISECONDS = 3600000;
    const double MINUTE_TO_MILLISECONDS = 60000;
    const double SECOND_TO_MILLISECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent),
  currentAmphoursUsed_(0),
  totalAmphoursUsed_((initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY)/100)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmphoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return (current_ < 0);
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
        double totalHoursRemaining;

        if(isCharging())
        {
            totalHoursRemaining = totalAmpHoursUsed() / current_ * -1;
        }
        else
        {
            totalHoursRemaining = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_;
        }

        while(totalHoursRemaining > 24)
        {
            totalHoursRemaining -= 24;
        }

        int hour = totalHoursRemaining;

        double millisecRemaining = (totalHoursRemaining - hour) * HOUR_TO_MILLISECONDS;
        int min = millisecRemaining / MINUTE_TO_MILLISECONDS;
        millisecRemaining = millisecRemaining - (min * MINUTE_TO_MILLISECONDS);
        int sec = millisecRemaining / SECOND_TO_MILLISECONDS;
        millisecRemaining = millisecRemaining - (sec * SECOND_TO_MILLISECONDS);
        int millisec = millisecRemaining;

        QTime timeRemaining(hour, min, sec, millisec);
        return timeRemaining;

}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    double oldCurrent = current_;
    current_ = batteryData.current;
    QTime oldTime = newTime_;
    newTime_ = batteryData.time;
    double averageCurrent = (oldCurrent + current_)/2;

    double changeInTimeMseconds = oldTime.msecsTo(newTime_);
    double hour = changeInTimeMseconds / 3600000;
    currentAmphoursUsed_ = hour * averageCurrent;
    totalAmphoursUsed_ = totalAmphoursUsed_ + currentAmphoursUsed_;
}
