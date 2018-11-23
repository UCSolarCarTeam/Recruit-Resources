#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MS_HOUR_CONVERSION = 3600000.0;
    const int PERCENT_TO_DECIMAL = 100;
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
    }
    else{
        return timeUntilDepleted;
    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if(batteryData.current<0){
        isCharging_=true;
    }
    else{
        isCharging_=false;
    }

    if(ampHourUsed==0.0){
        ampHourUsed=BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/PERCENT_TO_DECIMAL);
    }
    else{
        ampHourUsed+=((prevCurr+batteryData.current)/2)*((prevTime.msecsTo(batteryData.time))/MS_HOUR_CONVERSION) ;
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
    hourUntilCharged = hourUntilCharged.addMSecs((int)(hourCharge*MS_HOUR_CONVERSION));
    hourUntilDepleted = hourUntilDepleted.addMSecs((int)(hourDep*MS_HOUR_CONVERSION));
    timeUntilCharged = hourUntilCharged;
    timeUntilDepleted = hourUntilDepleted;
}
