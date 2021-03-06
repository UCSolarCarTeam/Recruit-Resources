#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, currentData_()
, previousData_()
, totalAmpHoursUsed_(initialStateOfChargePercent * BATTERY_AMP_HOUR_CAPACITY)
, averageCurrent_(0.0)
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
    if(currentData_.current < 0) //counting 0 as positive
    {
        return false;
    }

    return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double numberOfSecondsToWait;
    if(isCharging()) //if charging, then calculate time (in seconds) until fully charged
    {
        numberOfSecondsToWait = (totalAmpHoursUsed()/currentData_.current)*3600.0;
    }
    else //if not charging, then calculate time (in seconds) until fully depleted
    {
        double remainingAmpHours = BATTERY_AMP_HOUR_CAPACITY-totalAmpHoursUsed();
        numberOfSecondsToWait = (remainingAmpHours/currentData_.current)*3600.0;
    }

    return QTime(0, 0, 0, 0).addSecs(numberOfSecondsToWait);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //set new previous and current data
    previousData_ = currentData_;
    currentData_ = batteryData;

    //calculate average current
    averageCurrent_ = (averageCurrent_ + currentData_.current)/2.0;

    //calculate difference in time (in hours) between previous and current data
    double differenceInTimeInHrs = previousData_.time.secsTo(currentData_.time)/3600.0;
    if(differenceInTimeInHrs < 0)
    {
        differenceInTimeInHrs *= -1;
    }

    //update total amp hours used
    if(isCharging())
    {
        totalAmpHoursUsed_ -= (averageCurrent_ * differenceInTimeInHrs);
    }
    else
    {
        totalAmpHoursUsed_ += (averageCurrent_ * differenceInTimeInHrs);
    }
}
