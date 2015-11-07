#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), NewCurrent(0)
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
    if (NewCurrent<0)
        return false;
    else
        return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double TimeLeft;
    double Hours;
    double Minutes;
    double Seconds;
    double SumCurrent = 0;
    double counter;

    counter++;

     double TotalAverageCurrent;



    SumCurrent += InitialCurrent;

    TotalAverageCurrent = SumCurrent/counter;

    TimeLeft = (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/TotalAverageCurrent;

    TimeLeft = qAbs(TimeLeft);


    Hours = TimeLeft;
    int h = (int)TimeLeft;

    Minutes = (Hours-h)*60;
    int m = (int)Minutes;

    Seconds = (Minutes-m)*60;
    int s = (int)Seconds;

    int ms = (Seconds-s)*1000;

    QTime time(h, m, s, ms);


    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{



    double TimeChange;
    double AmpHChange;

     QTime InitialTime;


    InitialCurrent = NewCurrent;
    NewCurrent = batteryData.current;
     if (InitialCurrent == 0)
         AverageCurrent = NewCurrent;
     else
        AverageCurrent = (InitialCurrent+NewCurrent)/2;


    InitialTime = NewTime;
    NewTime = batteryData.time;
    TimeChange =InitialTime.msecsTo(NewTime);
    TimeChange = TimeChange * MILLISECONDS_TO_HOURS ;

    AmpHChange = AverageCurrent * TimeChange;
    AmpHours +=  AmpHChange;


}

