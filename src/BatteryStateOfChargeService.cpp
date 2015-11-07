#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), previousCurrent(0)
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
    if(previousCurrent<0)
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

    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-ampHours)/previousCurrent ;

    timeRemaining = qAbs(timeRemaining)/MILISECONDS_TO_HOURS;

    QTime time(0, 0, 0, 0);

    QTime t;

    t = time.addMSecs(timeRemaining);

    return t;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double newCurrent = batteryData.current;
    if(previousCurrent == 0)
    {
        aveCurrent = newCurrent;
    }
    else
    {
        aveCurrent = (previousCurrent+newCurrent)/2;
    }

    newTime = batteryData.time;
    dTime = previousTime.msecsTo(newTime);

    dTime = dTime*MILISECONDS_TO_HOURS;

    double dAmpHours = aveCurrent*dTime;
    ampHours += dAmpHours;

    previousTime = newTime;
    previousCurrent = newCurrent;
}
