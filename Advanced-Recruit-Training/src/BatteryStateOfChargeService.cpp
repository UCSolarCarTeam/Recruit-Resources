#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 3600000.0;
    const double SECONDS_TO_HOURS = 3600.0;
    const double HOURS_TO_MINUTES = 60.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
    , initialAmpHour_(BATTERY_AMP_HOUR_CAPACITY - (BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100))
    , counter_(0)
    , hour_(0)
    , current_(0)
    , isFirstTime_(true)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHour_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ < 0)
    {
       return true;
    }
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime timeTochargedOrDepleted(0,0,0,0);

    if(isCharging())
    {
     double timeToCharge;
     timeToCharge = totalAmpHour_ / current_;
     timeToCharge *= MILLISECONDS_TO_HOURS;
     timeTochargedOrDepleted = timeTochargedOrDepleted.addMSecs(qAbs(timeToCharge));

     return timeTochargedOrDepleted;
    }
    double timeToDepletion;
    timeToDepletion = (BATTERY_AMP_HOUR_CAPACITY-totalAmpHour_) / current_;
    timeToDepletion *= MILLISECONDS_TO_HOURS;
    timeTochargedOrDepleted = timeTochargedOrDepleted.addMSecs(qAbs(timeToDepletion));

    return timeTochargedOrDepleted;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    voltage_ = batteryData.voltage;
    current_ = batteryData.current;
    hour_ = batteryData.time.msecsTo(QTime(0,0,0.00));
    hour_ /= MILLISECONDS_TO_HOURS;
    hour_ *= -1;
    //using average of all values for current to calculate amp hours
    if(isFirstTime_)//the first hour read is stored in prevhour
    {
       prevHour_ = hour_;
       isFirstTime_ = false;
    }
    counter_++;
    averageCurrent_ *= (counter_ - 1);
    averageCurrent_ += current_;
    averageCurrent_ /= counter_;
    totalAmpHour_ = initialAmpHour_;
    totalAmpHour_ += averageCurrent_ * (hour_ - prevHour_);
}
