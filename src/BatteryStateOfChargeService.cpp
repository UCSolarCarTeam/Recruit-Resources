#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double hoursToMiliseconds = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), newCurrent(0)
{
    ampHours = (BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_)/100;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-ampHours ;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(newCurrent<0)
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
    //calculating the time remaining on the charge

    double sumCurrent = 0;
    double avesumCurrent;
    double hoursLeftOnCharge;
    double minutesLeftOnCharge;
    double secondsLeftOnCharge;
    double rowNumber;

    double timeRemaining;

    sumCurrent += previousCurrent;

    rowNumber++;

    qDebug()<< "rowNumber" <<rowNumber;
    avesumCurrent = sumCurrent/rowNumber;

    timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-ampHours)/avesumCurrent ;

    timeRemaining = qAbs(timeRemaining);

    //converting the time remaining into hours, seconds, minutes, and miliseconds


    hoursLeftOnCharge = timeRemaining;
    int hours = int(timeRemaining);
    int h = hours;

    minutesLeftOnCharge = (hoursLeftOnCharge-h)*60;
    int m = (int)minutesLeftOnCharge;

    secondsLeftOnCharge = (minutesLeftOnCharge - m)*60;
    int s = (int)secondsLeftOnCharge;

    int z = (secondsLeftOnCharge-s)*1000;

    QTime time(h, m, s, z);

    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);

    double dAmpHours;



    previousCurrent = newCurrent;
    newCurrent = batteryData.current;
    if(previousCurrent == 0)
    {
        aveCurrent = newCurrent;
    }
    else
    {
        aveCurrent = (previousCurrent+newCurrent)/2;
    }

    dAmpHours = aveCurrent*dTime;

    ampHours += dAmpHours;

    previousTime = newTime;
    newTime = batteryData.time;

    dTime = previousTime.msecsTo(newTime);

    dTime = dTime*hoursToMiliseconds;




}
