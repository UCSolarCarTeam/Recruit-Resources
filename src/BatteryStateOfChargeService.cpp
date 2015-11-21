#include "BatteryStateOfChargeService.h"
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, previousCurrent_(0)
{
    ampHours_ = (BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_) / 100;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - ampHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(previousCurrent_ < 0)
    {
       return false;
    }
    else
    {
       return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-ampHours_) / previousCurrent_;
    timeRemaining = qAbs(timeRemaining) / MILLISECONDS_TO_HOURS;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double presentCurrent = batteryData.current;
    if(previousCurrent_ == 0)
    {
        avgCurrent_ = presentCurrent;
    }
    else
    {
        avgCurrent_ = (previousCurrent_ + presentCurrent) / 2;
    }

    newTime_ = batteryData.time;
    deltaTime_ = previousTime_.msecsTo(newTime_);

    deltaTime_ = deltaTime_ * MILLISECONDS_TO_HOURS;

    double deltaAmpHours = avgCurrent_ * deltaTime_;
    ampHours_ += deltaAmpHours;

    previousTime_ = newTime_;
    previousCurrent_ = presentCurrent;
}
