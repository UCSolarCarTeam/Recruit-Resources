#include "BatteryStateOfChargeService.h"
#include <stdio.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    double ampHourTotal = 0;
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
    double diffOfHours = myTime.hour() - prevTime->hour();
    double diffOfMinutes = myTime.minute() - prevTime->minute();
    double diffOfSeconds = myTime.second() - prevTime->second();
    double diffOfMiliSec = myTime.msec() - prevTime->msec();
    double diffOfTime = diffOfSeconds + (diffOfMiliSec/1000);
    diffOfTime = diffOfMinutes + (diffOfSeconds/60);
    diffOfTime = diffOfHours + (diffOfMinutes/60);

    printf("diffInTime:%lf\n",diffOfTime);
    //printf("hours:%lf,minutes:%lf,seconds:%lf,millisec:%lf,time:%lf\n",diffOfHours,diffOfMinutes,diffOfSeconds,diffOfMiliSec,diffOfTime);
    //printf("curr hour:%i,minute:%i,second:%i,millis:%i\nprev hour:%i,minute:%i,second:%i,millis:%i\n",
      //     myTime.hour(),myTime.minute(),myTime.second(),myTime.msec(),prevTime->hour(),prevTime->minute(),prevTime->second(),prevTime->msec());


    double changeInAmpHour = myCurrent * diffOfTime;
    ampHourTotal += changeInAmpHour;
    return ampHourTotal;
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
    myVoltage = batteryData.voltage;
    myCurrent = batteryData.current;
    prevTime = new QTime(myTime.hour(),myTime.minute(),myTime.second(),myTime.msec());
    myTime = batteryData.time;
}
