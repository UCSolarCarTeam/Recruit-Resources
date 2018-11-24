#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

#define HOURS_TO_MS (3600.0 * 1000.0)

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

static double prevCurrent, current, voltage, totalAmpHours;
static QTime prevTime, currentTime;

//static QTime timeUntilCharged, timeUntilDepleted;

//Constructors
BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    initialAmpHours_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent/100);
    prevTime = QTime(0,0);
    totalAmpHours = initialAmpHours_;

}

double BatteryStateOfChargeService::totalAmpHoursUsed() const //using the most recent data points
{

    totalAmpHours += ((prevCurrent + current)/2) * ((prevTime.msecsTo(currentTime)) / HOURS_TO_MS);

    return totalAmpHours;
}
BatteryStateOfChargeService::~BatteryStateOfChargeService() //destructor
{
}
bool BatteryStateOfChargeService::isCharging() const
{
    return current < 0;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    if(isCharging())
    {
        double hourCharge = totalAmpHours/current;
        if(hourCharge < 0) {
            hourCharge *= -1;
        }
        QTime time = QTime(0,0);
        time = time.addMSecs((hourCharge * HOURS_TO_MS));
        return time;
    }

    double hoursUntilDepleted = (BATTERY_AMP_HOUR_CAPACITY -totalAmpHours)/current;
    QTime time = QTime(0,0);
    time = time.addMSecs(hoursUntilDepleted * HOURS_TO_MS);
    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    prevCurrent = current;
    current = batteryData.current;
    voltage = batteryData.voltage;

    prevTime = currentTime;
    currentTime = batteryData.time;
}
