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
: initialStateOfChargePercent_(initialStateOfChargePercent),
  current_(0),
  totalAmpHoursUsed_(0),
  checkStart_(true),
  timeDiff_(0)
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
   if (current_ < 0)
       return true;
   else
       return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return timeWhenChargedOrDepleted_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);


    if (checkStart_ == true)
    {
        totalAmpHoursUsed_ = (initialStateOfChargePercent_ / 100) * BATTERY_AMP_HOUR_CAPACITY;
    }

    else if (checkStart_ == false)
    {
        timeDiff_ = (double)(time_.msecsTo(batteryData.time) * MSECONDS_TO_HOURS_CONVERSION);
        double currentAverage = (batteryData.current + current_) / 2;
        totalAmpHoursUsed_ += currentAverage * timeDiff_;
    }

    time_ = batteryData.time;

    current_ = batteryData.current;

    checkStart_ = false;

    // The section below is for calculating the time it takes to charge or deplete
    int mSeconds;
    timeWhenChargedOrDepleted_.setHMS(0,0,0,0);

    if (isCharging())
    {
       mSeconds = (totalAmpHoursUsed_ / qAbs(current_)) * HOURS_TO_MSECONDS_CONVERSION;
       timeWhenChargedOrDepleted_ = timeWhenChargedOrDepleted_.addMSecs(mSeconds);
    }
    else
    {
        mSeconds = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_) / current_) * HOURS_TO_MSECONDS_CONVERSION;
        timeWhenChargedOrDepleted_ = timeWhenChargedOrDepleted_.addMSecs(mSeconds);
    }
}

