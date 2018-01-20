#include "BatteryData.h"
#include "BatteryStateOfChargeService.h"
#include <QTextStream>
#include <QDebug>


namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, amphoursUsed(0)
, previousCurrent(0)
, averageCurrent(0)
,check1(false)

{
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
if(averageCurrent<0){
    return true;
}else
{return false;}

}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{

    double timeUntilCharged;
    double timeUntilDepletion;

   QTime charged  (0,0,0,0);
   timeUntilCharged= (amphoursUsed/averageCurrent)*3600*1000;

   charged = charged.addMSecs(timeUntilCharged);



   QTime depletion (0,0,0,0);
   timeUntilDepletion=((BATTERY_AMP_HOUR_CAPACITY-amphoursUsed)*3600000)/averageCurrent;
   depletion = depletion.addMSecs(timeUntilDepletion);

   if (isCharging()==true){
        return charged;
    }else{
        return depletion;
    }


}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{








     double initialAmountOfAmphours = (initialStateOfChargePercent_/100) * BATTERY_AMP_HOUR_CAPACITY;

    if(check1)
    {
    averageCurrent = (batteryData.current+previousCurrent)/2;
    double timeIntervel = (double)previousTime.msecsTo(batteryData.time);
    double hours = timeIntervel/3600000;
    amphoursUsed += averageCurrent * hours;


    }
    else {
         amphoursUsed = initialAmountOfAmphours;

    }
check1 =true;
      previousTime=batteryData.time;
previousCurrent= batteryData.current;




    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
