#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <qdebug.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECOND_TO_HOUR_CONVERSION = 0.000000278;
    const int HOUR_TO_MILLISECOND = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHours_;
}
bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ < 0)
        return true;
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime timeToCompletion_(0, 0, 0, 0);
    if(current_ < 0) //charging
        return (timeToCompletion_.addMSecs(qAbs(totalAmpHoursUsed()/current_)*HOUR_TO_MILLISECOND));
    else    //depleting
        return (timeToCompletion_.addMSecs(((BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_)*HOUR_TO_MILLISECOND));
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    time_ = batteryData.time;
    current_ = batteryData.current;
    //time difference is 0 for the first and then previousTime_ is the previous for the next
    double timeDifference;
    timeDifference = (double) (previousTime_.msecsTo(time_)*MILLISECOND_TO_HOUR_CONVERSION);
    double currentAverage;
    currentAverage = (previousCurrent_ + current_)/2;
    previousTime_ = batteryData.time;
    previousCurrent_ = batteryData.current;
    additionalAmpHours_ += (currentAverage*timeDifference);

    totalAmpHours_ = (BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100) + additionalAmpHours_);
    qDebug() << currentAverage << endl;
    qDebug() << timeDifference << endl;
    qDebug() << additionalAmpHours_ << endl;
    qDebug() << totalAmpHours_ << endl;
}
