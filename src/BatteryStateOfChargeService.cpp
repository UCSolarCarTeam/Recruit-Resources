#include "BatteryStateOfChargeService.h"
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), newCurrent_(0)
{
    ampHours_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_ / 100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-ampHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newCurrent_ < 0)
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
    double timeLeft;

    timeLeft = (BATTERY_AMP_HOUR_CAPACITY - ampHours_) / newCurrent_;
    timeLeft = timeLeft / MILLISECONDS_TO_HOURS;
    timeLeft = qAbs(timeLeft);

    QTime baseTime (0, 0, 0, 0);
    QTime timeLeftTillDepletionOrCharge;
    timeLeftTillDepletionOrCharge = baseTime.addMSecs(timeLeft);

    return timeLeftTillDepletionOrCharge;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double timeChange;
    double changeInAmpHours;
    QTime previousTime;

    previousCurrent_ = newCurrent_;
    newCurrent_ = batteryData.current;

    if (previousCurrent_ == 0) //For the very first line of data
    {
        averageCurrent_ = newCurrent_;
    }
    else
    {
        averageCurrent_ = (previousCurrent_+newCurrent_)/2;
    }

    previousTime = newTime_;
    newTime_ = batteryData.time;
    timeChange = previousTime.msecsTo(newTime_);
    timeChange = timeChange * MILLISECONDS_TO_HOURS;

    changeInAmpHours = averageCurrent_ * timeChange;
    ampHours_ +=  changeInAmpHours;
}

