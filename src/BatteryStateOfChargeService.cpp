#include "BatteryStateOfChargeService.h"
#include <iostream>
#include <QTime>
#include <QDebug>
using namespace std;
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (Current < 0)
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
    return t;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    QTime currentTime = batteryData.time;
    changeTime = abs(initialTime.msecsTo(currentTime));
    changeTime = changeTime * 2.77778e-7;
    initialTime = currentTime;
    if ((Current > 0 && Current < 10000000000) || Current < 0 )
    {
        inCurrent = Current;
    }
    Current = batteryData.current;
    if (inCurrent == 0)
    {
        objectCurrent = 0;
    }
    else
    {
        objectCurrent = (inCurrent + Current)/2;
    }

    inVoltage = batteryData.voltage;
    Voltage = batteryData.voltage;
    AmpChange = (objectCurrent * changeTime);

    AmpHours += AmpChange;

    counter++;
    SumCurrent += inCurrent;
    AverageCurrent = SumCurrent/counter;
    TimeLeft= (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/AverageCurrent;
    TimeLeft = qAbs(TimeLeft) * 2.77778e-7;



    Hours = TimeLeft;
    int h = (int)TimeLeft;

    Minutes = (Hours-h)*60;
    int m = Minutes;

    Seconds = (Minutes-m)*60;
    int s = Seconds;

    int ms = (Seconds-s)*1000;

    QTime time(h,m,s,ms);
    t =  time;



    // Update your variables here.
}
