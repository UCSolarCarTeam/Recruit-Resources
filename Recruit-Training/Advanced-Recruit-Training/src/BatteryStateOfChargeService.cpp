#include "BatteryStateOfChargeService.h"
#include <QTextStream>
namespace
{
    const int DAY_IN_HOURS = 24;
    const double CONVERSION_FROM_HOURS_TO_MILLISECONDS = 3600000.0;
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
    : initialStateOfChargePercent_(initialStateOfChargePercent)
{
    //The initial amount of Amphours used would be the Battery’s Amphour capacity(Ah) multiplied by it’s state of charge(%)
    totalAmpHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    //The battery is charging when the battery current is negative, depleting when it is positive.
    if(batteryData_.current < 0)
        return true;
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    //The time until charge would be the Amphours used(Ah) divided by the current (A). Similarily, the time until depletion would be the remaining amphours divided by the current.
    double temp = (totalAmpHoursUsed_/batteryData_.current);
    if(temp<0)
        temp = -temp;
    while(temp>=DAY_IN_HOURS)
        temp -= DAY_IN_HOURS;
    temp *= CONVERSION_FROM_HOURS_TO_MILLISECONDS;
    return QTime::fromMSecsSinceStartOfDay((int)temp);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double diffHour = batteryData_.time.msecsTo(batteryData.time)/CONVERSION_FROM_HOURS_TO_MILLISECONDS;
    double changeInAmphours = ((batteryData.current+batteryData_.current)/2)*(diffHour);

    batteryData_ = batteryData;
    totalAmpHoursUsed_ += changeInAmphours;
    //The change in amphours used between two data points would be the average current(A) multiplied by the difference in time(h)
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
