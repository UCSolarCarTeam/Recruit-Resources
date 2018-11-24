#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_IN_AN_HOUR = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), totalAmpHoursUsed_(0.0), firstRun_(true)
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
    if(newCurrent_ < 0){
        return true;
    }
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double tempTime;
    if(isCharging())
    {
        tempTime = (totalAmpHoursUsed_/newCurrent_);
        tempTime = tempTime * -1;
    }
    else
    {
        tempTime = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_)/newCurrent_;
    }

    QTime timeWhenChargedOrDepleted(0,0,0,0);

    timeWhenChargedOrDepleted = timeWhenChargedOrDepleted.addMSecs((int)(tempTime * MILLISECONDS_IN_AN_HOUR));

    return timeWhenChargedOrDepleted;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if (totalAmpHoursUsed_ == 0.0 && firstRun_)
    {

        totalAmpHoursUsed_ = (initialStateOfChargePercent_/100.0) * BATTERY_AMP_HOUR_CAPACITY;
        previousTime_ = batteryData.time;
        newTime_ = batteryData.time;
        previousCurrent_ = batteryData.current;
        newCurrent_ = batteryData.current;
        firstRun_ = false;
    }
    else
    {
        previousTime_ = newTime_;
        newTime_ = batteryData.time;
        previousCurrent_ = newCurrent_;
        newCurrent_ = batteryData.current;
        averageCurrent_ = (newCurrent_ + previousCurrent_) / 2.0;
        changeInTime_ = (previousTime_.msecsTo(newTime_)) / (MILLISECONDS_IN_AN_HOUR);
        changeInAmpHours_ = (averageCurrent_ * changeInTime_);
        totalAmpHoursUsed_ += changeInAmpHours_;
         }
}
