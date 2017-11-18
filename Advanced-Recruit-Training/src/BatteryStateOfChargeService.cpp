#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTextStream>
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    batteryData_.current = 0;
    batteryData_.time.setHMS(0,0,0,0);
    batteryData_.voltage = 0;
    totalAmpHoursUsed_ = 0;
    ampHours_ = (initialStateOfChargePercent_/100)*BATTERY_AMP_HOUR_CAPACITY;
    dataPoints_ = 0;
    timeDiff_ = 0;
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
   if (batteryData_.current < 0)
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
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    // The section below is updates the total Amphours used
    if (dataPoints_ > 0)
        timeDiff_ = (double)(batteryData_.time.msecsTo(batteryData.time)*0.000000278);

    batteryData_.time = batteryData.time;

    if (dataPoints_ == 0)
        totalAmpHoursUsed_ = ampHours_;
    if (dataPoints_ > 0)
        totalAmpHoursUsed_ += (((batteryData.current + batteryData_.current) /2) * timeDiff_);

    batteryData_.current = batteryData.current;

    dataPoints_++;

    // The section below is for calculating the time it takes to charge or deplete
    double mSeconds;
    timeWhenChargedOrDepleted_.setHMS(0,0,0,0);

    if (batteryData_.current < 0)
    {
       mSeconds = (totalAmpHoursUsed_/(batteryData_.current*(-1)))*3600000;
       timeWhenChargedOrDepleted_= timeWhenChargedOrDepleted_.addMSecs((int)mSeconds);
    }

    else
    {
        mSeconds = ((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_)/batteryData_.current)*3600000;
        timeWhenChargedOrDepleted_ = timeWhenChargedOrDepleted_.addMSecs(mSeconds);
    }
}

