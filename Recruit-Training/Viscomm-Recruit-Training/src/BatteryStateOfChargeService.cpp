#include "BatteryStateOfChargeService.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HRS_TO_MS = 3600000.0;
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
    double numberOfMillisecondsToWait;
    if(isCharging()) //if charging, then calculate time (in ms) until fully charged
    {
        numberOfMillisecondsToWait = (totalAmpHoursUsed()/currentData_.current)*HRS_TO_MS;
    }
    else //if not charging, then calculate time (in ms) until fully depleted
    {
        double remainingAmpHours = BATTERY_AMP_HOUR_CAPACITY-totalAmpHoursUsed();
        numberOfMillisecondsToWait = (remainingAmpHours/currentData_.current)*HRS_TO_MS;
    }

    return QTime(0, 0, 0, 0).addMSecs(numberOfMillisecondsToWait);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //set new previous and current data
    previousData_ = currentData_;
    currentData_ = batteryData;

    //calculate average current
    averageCurrent_ = (averageCurrent_ + currentData_.current)/2.0;

    //calculate difference in time (in hours) between previous and current data
    double differenceInTimeInHrs = previousData_.time.msecsTo(currentData_.time)/HRS_TO_MS;
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
