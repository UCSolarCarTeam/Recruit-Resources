#include "BatteryStateOfChargeService.h"
#include <stdio.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    double ampHourTotal;
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


    //printf("hours:%lf,minutes:%lf,seconds:%lf,millisec:%lf,time:%lf\n",diffOfHours,diffOfMinutes,diffOfSeconds,diffOfMiliSec,diffOfTime);
    //printf("curr hour:%i,minute:%i,second:%i,millis:%i\nprev hour:%i,minute:%i,second:%i,millis:%i\n",
      //     myTime.hour(),myTime.minute(),myTime.second(),myTime.msec(),prevTime->hour(),prevTime->minute(),prevTime->second(),prevTime->msec());


    double avgCurrent = (myCurrent+prevCurrent)/2;

    double changeInAmpHour = avgCurrent * diffOfTime;
    ampHourTotal += changeInAmpHour;
    printf("AMPH:%lf",changeInAmpHour);
    return BATTERY_AMP_HOUR_CAPACITY- ampHourTotal;
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
    return QTime::currentTime();
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
