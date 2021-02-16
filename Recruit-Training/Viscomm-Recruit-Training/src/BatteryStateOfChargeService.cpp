#include "BatteryStateOfChargeService.h"
#include <cmath>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, currentData_(new BatteryData())
, pastData_(new BatteryData())
, totalCurrent_(0.0)
, currentCount_(0)
, totalAmpHours_(BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent / 100))
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
    delete pastData_;
    delete currentData_;
}

void BatteryStateOfChargeService::updateAmpHours(){

    if(pastData_->time.QTime::isNull()){
        return;
    }

    double currentAvg = totalCurrent_ / currentCount_;
    double timeDifference = pastData_->time.QTime::msecsTo(currentData_->time) / 3600000.0;
    double ampHoursDifference = currentAvg * timeDifference;

    if(isCharging()){
        totalAmpHours_ += ampHoursDifference;
    } else{
        totalAmpHours_ -= ampHoursDifference;
    }
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(currentData_->current > 0.0){
        return true;
    }

    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    int totalMsecs;
    double currentAvg = totalCurrent_ / currentCount_;
    if(isCharging()){
        double chargingHours = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHours_) / currentAvg;
        totalMsecs = chargingHours * 3600000;
    } else {
        double depletionHours = totalAmpHours_ / currentAvg;
        totalMsecs = depletionHours * 3600000;
    }

    return QTime(0, 0, 0, 0).QTime::addMSecs(totalMsecs);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    delete pastData_;
    pastData_ = currentData_;
    BatteryData* passedData = new BatteryData(batteryData.time, batteryData.voltage, batteryData.current);
    currentData_ = passedData;
    totalCurrent_ += abs(currentData_->current);
    currentCount_++;
    updateAmpHours();
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
