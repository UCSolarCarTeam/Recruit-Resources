#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_IN_AN_HOUR = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, firstRun_(true)
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
    if(presentCurrent_ < 0)
    {
        return true;
    }
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double tempTime;
    if(isCharging())
    {
        tempTime = (totalAmpHoursUsed_ / presentCurrent_);
        tempTime = tempTime * -1;
    }
    else
    {
        tempTime = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / presentCurrent_;
    }

    QTime timeWhenChargedOrDepleted(0,0,0,0);

    timeWhenChargedOrDepleted = timeWhenChargedOrDepleted.addMSecs((int)(tempTime * MILLISECONDS_IN_AN_HOUR));

    return timeWhenChargedOrDepleted;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double previousCurrent_;
    QTime previousTime_;
    double changeInTime_;
    double averageCurrent_;
    double changeInAmpHours_;

    if (firstRun_)
    {
        totalAmpHoursUsed_ = (initialStateOfChargePercent_ / 100.0) * BATTERY_AMP_HOUR_CAPACITY;

        firstRun_ = false;
    }

    previousTime_ = presentTime_;
    presentTime_ = batteryData.time;

    previousCurrent_ = presentCurrent_;
    presentCurrent_ = batteryData.current;

    averageCurrent_ = (presentCurrent_ + previousCurrent_) / 2.0;

    changeInTime_ = (previousTime_.msecsTo(presentTime_)) / (MILLISECONDS_IN_AN_HOUR);

    changeInAmpHours_ = (averageCurrent_ * changeInTime_);

    totalAmpHoursUsed_ += changeInAmpHours_;

}
