#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    amp_hour_used = 0.0;
    time_til_charged = QTime (0,0,0,0);
    time_til_depleted = QTime (0,0,0,0);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return amp_hour_used;
}

bool BatteryStateOfChargeService::isCharging() const
{
return is_charging;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   if(is_charging)
      return time_til_charged;
   else
      return time_til_depleted;

}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    const double ms2hour = 1/3600000.0;
    const double per2dec = 0.01;
        if(amp_hour_used == 0.0)
        {
             amp_hour_used = BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_*per2dec;
        }
        else{
             amp_hour_used+= ((previous_current+batteryData.current)/2)*((previous_time).msecsTo(batteryData.time)*ms2hour);
        }

    if(batteryData.current >= 0){
        is_charging = false;
    }
    else{
        is_charging = true;
    }

    previous_current = batteryData.current;
    previous_time = batteryData.time;
    hour_charge = amp_hour_used/batteryData.current;
    if(hour_charge<0){
        hour_charge *= -1;
    }
    hour_used = (BATTERY_AMP_HOUR_CAPACITY-amp_hour_used)/batteryData.current;
    QTime hour_til_charged = QTime (0,0,0,0);
    QTime hour_til_depleted = QTime (0,0,0,0);

    hour_til_charged = hour_til_charged.addMSecs((int)(hour_charge/ms2hour));
    hour_til_depleted = hour_til_depleted.addMSecs((int)(hour_used/ms2hour));
    time_til_charged = hour_til_charged;
    time_til_depleted = hour_til_depleted;
}
