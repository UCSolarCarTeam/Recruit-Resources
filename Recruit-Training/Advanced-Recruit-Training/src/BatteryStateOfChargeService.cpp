#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS = 3600000.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    totalAmpHoursUsed_ = 0.0;
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
    if(isCharging()){
        tempTime = (totalAmpHoursUsed_/newCurrent_);
    }
    else{
        tempTime = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed_)/newCurrent_;
    }
    if(tempTime < 0.0){
        tempTime = tempTime*-1;
    }
    QTime timeWhenChargedorDepleted = QTime(0,0,0,0);

    timeWhenChargedorDepleted = timeWhenChargedorDepleted.addMSecs((int)(tempTime*MILLISECONDS));

    return timeWhenChargedorDepleted;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Q_UNUSED(batteryData);
    if (totalAmpHoursUsed_ == 0.0)
        {
            totalAmpHoursUsed_ = (initialStateOfChargePercent_/100.0) * BATTERY_AMP_HOUR_CAPACITY;
            previousTime_ = batteryData.time;
            newTime_ = batteryData.time;
            previousCurrent_ = batteryData.current;
            newCurrent_ = batteryData.current;
        }
    else
         {
            previousTime_ = newTime_;
            newTime_ = batteryData.time;
            previousCurrent_ = newCurrent_;
            newCurrent_ = batteryData.current;
            changeInAmpHours_ = ((newCurrent_ + previousCurrent_)/2.0) * (previousTime_.msecsTo(newTime_)/(MILLISECONDS));
            totalAmpHoursUsed_ += changeInAmpHours_;
         }

    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
