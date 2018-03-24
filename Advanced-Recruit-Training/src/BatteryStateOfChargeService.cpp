#include "BatteryData.h"
#include "BatteryStateOfChargeService.h"
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int hourIntoMsec = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, amphoursUsed(0)
, previousCurrent(0)
, averageCurrent(0)
, current(0)
, firstTime(false)

{
    initialAmountOfAmphours_ = (initialStateOfChargePercent_/100) * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
     return amphoursUsed;
}

bool BatteryStateOfChargeService::isCharging() const
{
      if(current < 0)
{
    return true;
}
    else
{
        return false;
}
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
 {
    double timeUntilCharged;
    double timeUntilDepletion;

    QTime charged  (0,0,0,0);
    timeUntilCharged= (amphoursUsed / current)*(hourIntoMsec);

    charged = charged.addMSecs(timeUntilCharged);
    QTime depletion (0,0,0,0);
    timeUntilDepletion=((BATTERY_AMP_HOUR_CAPACITY-amphoursUsed)*hourIntoMsec)/current;
    depletion = depletion.addMSecs(qAbs(timeUntilDepletion));

   if (isCharging)
    {
        return charged;
    }else{
        return depletion;
    }
}
void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
current = batteryData.current;
if(firstTime)
{
    averageCurrent = (batteryData.current+previousCurrent)/2;
    double timeInterval = (double)previousTime.msecsTo(batteryData.time);
    double hours = timeInterval/hourIntoMsec;
    amphoursUsed += averageCurrent * hours;
}
    else
{
    amphoursUsed = initialAmountOfAmphours_;
}
firstTime =true;
    previousTime=batteryData.time;
    previousCurrent= batteryData.current;
}
