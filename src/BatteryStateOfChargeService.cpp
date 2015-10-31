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
    return t;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);
    // Update your variables here.
    initialCurrent = newCurrent;
    newCurrent = batteryData.current;
    if(initialCurrent == 0)
    {
        aveCurrent = newCurrent;
    }
    else
    {
        aveCurrent = (initialCurrent+newCurrent)/2;
    }
    initialTime = newTime;
    newTime = batteryData.time;

    dAmpHours = aveCurrent*dTime;
    //qDebug() << "new time" << newTime;
    //qDebug() << "initial time" <<initialTime;
    dTime = initialTime.msecsTo(newTime);

    dTime = dTime*2.77778e-7;

    ampHours += dAmpHours;

    count++;

    currentPrime += initialCurrent;

    aveCurrentPrime = currentPrime/count;

    timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-ampHours)/aveCurrentPrime ;

    timeRemaining = qAbs(timeRemaining);

    hoursPrime = timeRemaining;
    int hours = int(timeRemaining);
    int h = hours;

    minutesPrime = (hoursPrime-h)*60;
    int m = (int)minutesPrime;

    secondsPrime = (minutesPrime - m)*60;
    int s = (int)secondsPrime;

    int z = (secondsPrime-s)*1000;
    int a = 2;

    //qDebug() << "time remaining" << timeRemaining;
    //qDebug() << "amp hours" << ampHours;

    //QTime time;

    //time = time.addSecs((int)ms);

    QTime time(h, m, s, z);
    t = time;
    //QString TimetoDepletion = t.toString("hh:mm:ss.zzz");

   /* qDebug() << " " << h;
    qDebug() << " " << m;
    qDebug() << " " << s;
    qDebug() << " " << z;
*/
   //qDebug() << " " << t;


/*
    rateofDepletion = dAmpHours/dTime;





    //qDebug() << " " << timeRemaining;

    //timeRemaining = timeRemaining/2.777778e-7;

    qDebug()<< "time remaining" << timeRemaining;


*/

}
