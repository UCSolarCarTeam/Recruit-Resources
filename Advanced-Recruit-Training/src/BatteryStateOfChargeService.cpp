#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QDebug>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{

}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{

}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - (initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY);
}

bool BatteryStateOfChargeService::isCharging() const
{

    if(current_> 0)
        return false;
    return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   int charging = (totalAmpHoursUsed()/current_)*3600000;
   int depleting = ((BATTERY_AMP_HOUR_CAPACITY  - totalAmpHoursUsed())/current_)*3600000;
   QTime time(0,0,0,0);

   qDebug() << "Test:" << time.addMSecs(charging);
   if(current_< 0)
      return time.addMSecs(charging);

   else
       return time.addMSecs(depleting);

}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    // This is where you can update your variables
    current_ = batteryData.current;
    voltage_ = batteryData.voltage;

}
