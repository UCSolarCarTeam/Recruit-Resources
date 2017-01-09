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
    double totalcurrent= 0;
    totalcurrent= ( (current1 * ( counter - 1) )/ counter + (current/counter) );
    return totalcurrent;
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

    double init=    initialStateOfChargePercent_;
    double avg= ( (current / BATTERY_AMP_HOUR_CAPACITY )) * 100;
    if(avg <= 0)
    {
        avg= -avg;
    }
    double averageMin=0; //current/60 will be current per minutes
    double averageSec=0; //average min /60 will be current per seconds
    int hours=0;   //variable to multiply by 3600
    int minutes=0; //variable to multiply by 60
    int seconds=0; //variable to multiply by 1
    if(isCharging())
    {
        while(init < 99.99)
        {
            if(( init + avg ) >= 100 )
            {
                averageMin = ( (100 - init) / avg)*100;
                init = averageMin + init; //add to init the minute val
                minutes += 1; //add one to variable minute
                if ( (averageMin+init) >= 100)
                {
                    averageSec = ( (100-init) / averageMin ) * 100;
                    init = init + averageSec; //adding the sec % charge
                    seconds += 1; //adding a second variable to it
                    if (averageSec + init >= 100) //if its greater than end it !
                    {
                        int adder = hours * 3600 + minutes * 60 + seconds; //Multiply these variable by their second values
                        QTime time1 = time.addSecs(adder); //add it to a new time
                        return time1; //return my final time
                    }
                }
            }
            else
            {
                hours += 1;
                init = init + avg;
            }
        }
    }
    else
    {
        while(init > 0.001)
        {
            if( ( init - avg ) < 0 )
            {
                averageMin = ((100-init) / avg) * 100;

                init = init - averageMin;
                minutes += 1;
                if( (init - averageMin) < 100)
                {
                    averageSec =( (100-init) / averageMin) * 100;//this should be like 99.4%
                    init = init - averageSec;
                    seconds += 1;
                    if( (init-averageSec) <= 0)
                    {
                        int adder = hours * 3600 + minutes * 60 + seconds;
                        QTime time1 = time.addSecs(adder);
                        return time1;
                    }
                }
            }
            else
            {
                hours += 1;
                init = init - avg;
            }
        }
    }
    int adder = hours * 3600 + minutes * 60 + seconds;
    QTime time1 = time.addSecs(adder);
    return time1;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    {
        current = batteryData.current; //get the current value
        time = batteryData.time; //get the time variable stamp
        counter = counter+1; //add one to the counter
        current1 = totalAmpHoursUsed(); //call the funciton to change it
        isCharging(); //call to change it
        timeWhenChargedOrDepleted();
    }
}
