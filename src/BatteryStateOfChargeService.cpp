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
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (CurrentPrime<0)
        return false;
    else
        return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{

    return t;
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
    AmpHours +=  AmpHChange;

    counter++;

    NewCurrent += InitialCurrent;

    AverageCurrentPrime = NewCurrent/counter;

    TimeLeft = (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/AverageCurrentPrime;

    TimeLeft = qAbs(TimeLeft);

    HoursPrime = TimeLeft;
    int h = (int)TimeLeft;

    MinutesPrime = (HoursPrime-h)*60;
    int m = (int)MinutesPrime;

    SecondsPrime = (MinutesPrime-m)*60;
    int s = (int)SecondsPrime;

    int ms = (int)(SecondsPrime-s)*1000;

    QTime time(h, m, s, ms);
    t = time;




}

