#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTextStream>

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
    double totalcurrent=0;//set it to zero
    totalcurrent=((current1*(counter-1))/counter+(current/counter));//+current;//the running total plus the number passed in
    return totalcurrent;//return the running val
}

bool BatteryStateOfChargeService::isCharging() const
{
    //current=BatteryData(c);
    if(current<0)//negative means charging
    {
        return true;//:)
    }
    else//positive means running
    {
    return false;//bad
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{

    double init=initialStateOfChargePercent_;//get the starting avg of charge
    double avg=((current/BATTERY_AMP_HOUR_CAPACITY))*100;//get the avg increase of charge
    if(avg<=0)//ABS wasnt working for some odd reason???
    {
        avg=-avg;//just make it positive if not
    }
    double averagemin=0;//current/60 will be current per minutes
    double averagesec=0;//average min /60 will be current per seconds
    int hours=0;//variable to multiply by 3600
    int minutes=0;//variable to multiply by 60
    int seconds=0;//variable to multiply by 1
    if(isCharging())//if the car is charging here is the math m8
    {
        while((init<99.99))//it will never exactly equal 100
        {
            if((init+avg)>=100)//if its like 99% charged then it will be minutes
            {
                //ok so were done with hours now we need minutes???
                averagemin=((100-init)/avg);// 100 -like 96 will be like 4% left then divide by the current avg for minute
                init=averagemin+init;//add to init the minute val
                minutes+=1;//add one to variable minute
                if((averagemin+init)>=100)//this would be like 99%
                {
                    averagesec=((100-init)/averagemin)*100;//this should be like 99.4%
                    init=init+averagesec;//adding the sec % charge
                    seconds+=1;//adding a second variable to it
                    if(averagesec+init>=100)//if its greater than end it !
                    {
                        int adder=hours*3600+minutes*60+seconds;//Multiply these variable by their second values
                        QTime time1=time.addSecs(adder);//add it to a new time
                        return time1;//return my final time
                    }
                }

            }
            else
            {
                hours+=1;//if its like 40 percent it will just add the number
                init=init+avg;
            }

        }

    }
    else//ITs running gonna be subtracting
    {//i did abs value calcs.
        while(init>0.001)//while it isnt less that one
        {
            if((init-avg)<0)//if its like 99% charged then it will be minutes
            {
                //ok so were done with hours now we need minutes???
                averagemin=((100-init)/avg)*100;
                init=init-averagemin;
                minutes+=1;
                if((init-averagemin)<100)
                {
                    averagesec=((100-init)/averagemin)*100;//this should be like 99.4%
                    init=init-averagesec;
                    seconds+=1;
                    if((init-averagesec)<=0)
                    {
                        int adder=hours*3600+minutes*60+seconds;
                        QTime time1=time.addSecs(adder);
                        return time1;
                    }
                }

            }
            else
            {
                hours+=1;//if its like 40 percent it will just add the number
                init=init-avg;
            }

        }


    }
    int adder=hours*3600+minutes*60+seconds;
    QTime time1=time.addSecs(adder);
    return time1;//all such commented above
           }


void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    {

        //this need to be global no idea in C++
       // Q_UNUSED(batteryData);//get the data from batteryData
       // double current= &batteryData->current;
        current= batteryData.current;//get the current value
        time=batteryData.time;//get the time variable stamp
        counter=counter+1;//add one to the counter
        current1=totalAmpHoursUsed();//call the funciton to change it
        isCharging();//call to change it
        timeWhenChargedOrDepleted();
        // This is where you can update your variables
        // Hint: There are many different ways that the totalAmpHoursUsed can be updated
        // i.e: Taking a running average of your data values, using most recent data points, etc.
    }
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.
}
