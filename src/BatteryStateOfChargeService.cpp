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
    return ampHours;
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

    ampHours -= dAmpHours;

    //qDebug() << "amp hours" << ampHours;




}
