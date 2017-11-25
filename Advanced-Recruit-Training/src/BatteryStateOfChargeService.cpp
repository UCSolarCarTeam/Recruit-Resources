#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTextStream>
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOURS_TO_MSECONDS_CONVERSION = 3600000;
    const double MSECONDS_TO_HOURS_CONVERSION = 0.000000278;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, previousCurrent_(0)
, totalAmpHoursUsed_((initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY)
, checkStart_(true)
, timeDiff_(0)
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
   if (previousCurrent_ < 0)
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
    return timeWhenChargedOrDepleted_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if (checkStart_)
    {
        checkStart_ = false;
    }
    else
    {
        timeDiff_ = (double)(previousTime_.msecsTo(batteryData.time)) * MSECONDS_TO_HOURS_CONVERSION;
        double currentAverage = (batteryData.current + previousCurrent_) / 2;
        totalAmpHoursUsed_ += currentAverage * timeDiff_;
    }

    previousTime_ = batteryData.time;

    previousCurrent_ = batteryData.current;

    // The section below is for calculating the time it takes to charge or deplete
    int mSeconds;
    timeWhenChargedOrDepleted_.setHMS(0,0,0,0);

    if (isCharging())
    {
       mSeconds = (totalAmpHoursUsed_ / qAbs(previousCurrent_)) * HOURS_TO_MSECONDS_CONVERSION;
       timeWhenChargedOrDepleted_ = timeWhenChargedOrDepleted_.addMSecs(mSeconds);
    }
    else
    {
        mSeconds = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / previousCurrent_) * HOURS_TO_MSECONDS_CONVERSION;
        timeWhenChargedOrDepleted_ = timeWhenChargedOrDepleted_.addMSecs(mSeconds);
    }
}

