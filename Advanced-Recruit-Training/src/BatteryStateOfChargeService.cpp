#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MS_TO_HOURS = 3600000.0;
    const double S_TO_HOURS = 3600.0;
    const double HOUR_TO_M = 60.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    initalAmpHour_=BATTERY_AMP_HOUR_CAPACITY-BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_/100;
    counter_=0;
    hour_=0;
    current_=0;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{

    return totalAmpHour_;
}

bool BatteryStateOfChargeService::isCharging() const
{

    if(current_<0){
       return true;
    }
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{    QTime charging;
     charging.setHMS(0,0,0,0);

    if(isCharging()){
    charging= charging.addMSecs(qAbs(totalAmpHour_/current_*MS_TO_HOURS));

     return charging;
    }

   charging = charging.addMSecs(qAbs(( BATTERY_AMP_HOUR_CAPACITY-totalAmpHour_)/current_*MS_TO_HOURS));
    return charging;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);

    voltage_ = batteryData.voltage;
    current_ = batteryData.current;

    hour_= batteryData.time.hour()
            +batteryData.time.minute()/HOUR_TO_M
            +batteryData.time.second()/S_TO_HOURS
            +batteryData.time.msec()/MS_TO_HOURS;
    //using running average of current to calculate amp hours
    if(counter_==0){    //the first hour read is stored in prevhour
       prevHour_=hour_;
    }

    counter_++;
    averageCurrent_ =(averageCurrent_*(counter_-1.0)+current_)/counter_;
    totalAmpHour_=initalAmpHour_+averageCurrent_*(hour_-prevHour_);

}
