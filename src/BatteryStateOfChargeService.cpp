#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_/100);
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
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return QTime::currentTime();
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    InitialCurrent = CurrentPrime;
    CurrentPrime = batteryData.current;
     if (InitialCurrent == 0)
         AverageCurrent = CurrentPrime;
     else
        AverageCurrent = (InitialCurrent+CurrentPrime)/2;

    InitialTime = TimePrime;
    TimePrime = batteryData.time;
    TimeChange =InitialTime.msecsTo(TimePrime);
    TimeChange = TimeChange * 2.77778e-7;

    AmpHChange = AverageCurrent * TimeChange;
    AmpHours -= AmpHChange;



}
