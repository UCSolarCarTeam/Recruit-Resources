#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_PER_HOUR = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, remainingAmpHours_(initialStateOfChargePercent_ / 100.0 * BATTERY_AMP_HOUR_CAPACITY)
, isFirstRun_(true)
, oldCurrent_(0)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - remainingAmpHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (data_.current < 0)
    {
        return true;
    }
    else
    {
       return false;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double hoursTillChargedOrDepleted; double ampHours;
    if(isCharging())
    {
        ampHours = totalAmpHoursUsed();
    }
    else
    {
        ampHours = remainingAmpHours_;
    }
    hoursTillChargedOrDepleted = ampHours / data_.current;
    hoursTillChargedOrDepleted = abs(hoursTillChargedOrDepleted);

    int milliseconds = hoursTillChargedOrDepleted * MILLISECONDS_PER_HOUR;
    QTime result(0, 0, 0);
    return result.addMSecs(milliseconds);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    data_ = batteryData;

    if(isFirstRun_)
    {
        oldCurrent_ = abs(data_.current);
        oldTime_ = data_.time;
        isFirstRun_ = false;
        return;
    }

    double newCurrent = abs(data_.current);
    QTime newTime = data_.time;

    int differenceInTimeMilis = oldTime_.msecsTo(newTime);
    double differenceInHours = differenceInTimeMilis / MILLISECONDS_PER_HOUR;
    double usedAmpHours = (newCurrent + oldCurrent_) / 2.0;
    usedAmpHours *= differenceInHours;

    if(isCharging())
        remainingAmpHours_ += usedAmpHours;
    else
        remainingAmpHours_ -= usedAmpHours;

    oldCurrent_ = newCurrent;
    oldTime_ = newTime;
}
