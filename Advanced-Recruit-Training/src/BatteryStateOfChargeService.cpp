#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    initalAmpHour_= BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_/100;
    counter_=0;
    hour_=0;
    current_=0;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{

    return ampHour_;
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

    if(isCharging()==true){
    charging= charging.addMSecs(qAbs(ampHour_/current_*3600000));

     return charging;
    }

   charging = charging.addMSecs(qAbs(( BATTERY_AMP_HOUR_CAPACITY-ampHour_)/current_*3600000));
    return charging;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    Q_UNUSED(batteryData);

    voltage_ = batteryData.voltage;
    current_ = batteryData.current;

    hour_= batteryData.time.hour()+batteryData.time.minute()/60.0+batteryData.time.second()/3600.0+batteryData.time.msec()/3600000.0;
    //using running average of current to calculate amp hours
    if(counter_==0){    //the first hour read is stored in prevhour
    prevHour_=hour_;
}

    counter_++;
    averageCurrent_ =(averageCurrent_*(counter_-1.0)+current_)/counter_;
    ampHour_=initalAmpHour_+averageCurrent_*(hour_-prevHour_);
}
