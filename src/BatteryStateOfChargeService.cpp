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
    return AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (Current - inCurrent < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double Rtime = (Voltage/((Voltage-inVoltage)/changeTime));
    QTime tie = QTime(0,0).addMSecs(Rtime * 3600000);
    // QString chTime = QString::number(Rtime);
    // QTime tie = QTime::fromString(chTime,"hh:mm:ss.zzz");
    return tie;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Time
    QTime currentTime = batteryData.time;
    changeTime = abs(initialTime.msecsTo(currentTime));
    changeTime = changeTime * 2.77778e-7;
    initialTime = currentTime;
    //Current
    inCurrent = batteryData.current;
    Current = batteryData.current;
    objectCurrent = (inCurrent + Current)/2;
    //Amp Hours    //Voltage
    inVoltage = batteryData.voltage;
    Voltage = batteryData.voltage;
    AmpHours = AmpHours - (objectCurrent * changeTime);


    // Update your variables here.
}
