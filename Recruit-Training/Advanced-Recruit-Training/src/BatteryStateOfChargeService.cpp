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
    timeUntilCharged = QTime(0,0,0,0);
    timeUntilDepleted = QTime(0,0,0,0);
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
        return timeUntilCharged;
    }else{
        return timeUntilDepleted;

    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
   // Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
    const double ms_hour_conversion = 3600000.0;
    const int percent_to_decimal = 100;
    if(batteryData.current<0){
        isCharging_=true;
    }else{
        isCharging_=false;
    }

    if(ampHourUsed==0.0){
        ampHourUsed=BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/percent_to_decimal);
    }
    else{
        ampHourUsed+=((prevCurr+batteryData.current)/2)*((prevTime.msecsTo(batteryData.time))/ms_hour_conversion) ;
    }
    prevCurr = batteryData.current;
    prevTime = batteryData.time;
    hourCharge = ampHourUsed/batteryData.current;
    if(hourCharge<0){
        hourCharge = hourCharge*-1;
    }
    hourDep = (BATTERY_AMP_HOUR_CAPACITY-ampHourUsed)/batteryData.current;
    QTime hourUntilCharged = QTime(0,0,0,0);
    QTime hourUntilDepleted = QTime(0,0,0,0);
    hourUntilCharged = hourUntilCharged.addMSecs((int)(hourCharge*ms_hour_conversion));
    hourUntilDepleted = hourUntilDepleted.addMSecs((int)(hourDep*ms_hour_conversion));
    timeUntilCharged = hourUntilCharged;
    timeUntilDepleted = hourUntilDepleted;
}
