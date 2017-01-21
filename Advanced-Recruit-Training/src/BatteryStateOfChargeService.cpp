#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"

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
    return currentAmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{   
    if( current < 0 )
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
    double initialValueOfCharge = initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY; //initial state in miliseconds
    double averageIncreaseValue = totalAmpHoursUsed() * 3.6e+6 ; //the increase in charge
    if(averageIncreaseValue <= 0)
    {
        averageIncreaseValue = -averageIncreaseValue;
    }
    if( isCharging() )
    {
        // Ah / a
        double batteryChargeRemaining = (averageIncreaseValue * 3.6e+6) * (BATTERY_AMP_HOUR_CAPACITY-initialValueOfCharge) / -current; //BatteryAMPHOUR should be totalAMpHour
        double timeLeft = batteryChargeRemaining / averageIncreaseValue;
        QTime timeUntilFinished = currentTime.addMSecs(timeLeft);
        return timeUntilFinished;
    }
    else
    {
        //Ah x V / Watts
        double timeLeft = ((averageIncreaseValue * voltage * 3.6e+6 * initialValueOfCharge) / -(voltage * current));    //AH value passed around
        QTime timeUntilFinished = currentTime.addMSecs(timeLeft);
        return timeUntilFinished;
    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    {
        voltage = batteryData.voltage;
        current = batteryData.current; //get the current value
        if(currentTime.toString() == NULL)
        {
            previousTime = QTime(0,0,0);
        }
        else
        {
            previousTime = currentTime;
        }
        currentTime = batteryData.time;
        timeDifferenceStamp = currentTime.toString( "hhmmss.zzz").toDouble() - previousTime.toString( "hhmmss.zzz" ).toDouble();

        currentAmpHours = currentAmpHours + current/timeDifferenceStamp;

        //This was moved form above
        isCharging(); //call to change it
        timeWhenChargedOrDepleted();
    }
}
