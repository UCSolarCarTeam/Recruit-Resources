#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHourUsed=0.0;
    holdC = QTime(0,0,0,0);
    holdD = QTime(0,0,0,0);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHourUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
   return isCharging_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    if(isCharging_){
        return holdC;
    }else{
        return holdD;

    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
   // Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    if(batteryData.current<0){
        isCharging_=true;
    }else{
        isCharging_=false;
    }

    if(ampHourUsed==0.0){
        ampHourUsed=BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
    }
    else{
        ampHourUsed+=((prevCurr+batteryData.current)/2)*((prevTime.msecsTo(batteryData.time))/3600000.0) ;
    }
    prevCurr = batteryData.current;
    prevTime = batteryData.time;
    hourCharge = ampHourUsed/batteryData.current;
    if(hourCharge<0){
        hourCharge = hourCharge*-1;
    }
    hourDep = (BATTERY_AMP_HOUR_CAPACITY-ampHourUsed)/batteryData.current;
    QTime hourC = QTime(0,0,0,0);
    QTime hourD = QTime(0,0,0,0);
    hourC = hourC.addMSecs((int)(hourCharge*3600000.0));
    hourD = hourD.addMSecs((int)(hourDep*3600000.0));
    holdC = hourC;
    holdD = hourD;
}
