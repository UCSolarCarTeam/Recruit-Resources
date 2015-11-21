#include "BatteryStateOfChargeService.h"
#include <stdio.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    double ampHourTotal;
    double ampHourUsed;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHourTotal = (initialStateOfChargePercent_/100) * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    double diffOfTimeMSec = prevTime->msecsTo(myTime);
    double diffOfTime = diffOfTimeMSec/3600000;
    double avgCurrent = (myCurrent+prevCurrent)/2;

    double changeInAmpHour = avgCurrent * diffOfTime;
    ampHourTotal += changeInAmpHour;
    //if(ampHourTotal > BATTERY_AMP_HOUR_CAPACITY){ampHourTotal = BATTERY_AMP_HOUR_CAPACITY;}
    ampHourUsed = BATTERY_AMP_HOUR_CAPACITY- ampHourTotal;
    return ampHourUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(myCurrent>=0)
    {
        return false;
    }
    return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double ampHoursLeft;
    if(isCharging())
    {
        ampHoursLeft = BATTERY_AMP_HOUR_CAPACITY - ampHourTotal;
    }
    else
    {
        ampHoursLeft = ampHourTotal;
    }
    int current = myCurrent;
    if(myCurrent < 0)
    {
        current *= -1;
    }
    double msecLeft = (ampHoursLeft * 3600000) / current;
    QTime QTimeLeft = QTime(0,0,0,0);
    QTimeLeft = QTimeLeft.addMSecs(msecLeft);
    return QTimeLeft;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if(myTime.isNull())
    {
        prevTime = new QTime(0,0,0,0);
    }
    myVoltage = batteryData.voltage;
    prevCurrent = myCurrent;
    myCurrent = batteryData.current;
    prevTime = new QTime(myTime.hour(),myTime.minute(),myTime.second(),myTime.msec());
    myTime = batteryData.time;
}
