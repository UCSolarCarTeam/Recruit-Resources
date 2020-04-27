#include "BatteryStateOfChargeService.h"
#include "BatteryData.h"
#include <QTime>
#include <math.h>
#include <QTextStream>
#include <QString>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), timeWhenChargedOrDepleted_(1,1,1,1), old_current(0), present_batterycurrent(0), totalAmpHoursUsed_(0), isCharging_(0)
{
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
    return isCharging_;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   return timeWhenChargedOrDepleted_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    //Q_UNUSED(batteryData);
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    old_current=present_batterycurrent;
    present_batterycurrent = batteryData.current;
    old_time=present_time;
    present_time= batteryData.time;

    //total AmpHours Used
    double initial_amountof_amphours_used =BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_/100;
    double average_current= (present_batterycurrent+old_current)/2;


    if (old_time.isValid())
    {
     double time_difference_in_hours= old_time.msecsTo(present_time)/3600000.0;// For some reason this comes out to 0
     //QString s= old_time.toString("hh:mm:ss:zzz");
     //QString t= present_time.toString("hh:mm:ss:zzz");
     //QTextStream(stdout)<<s<<"      "<<t<<"     "<< time_difference_in_hours<<"     "<< average_current<< "    ";
    totalAmpHoursUsed_+= average_current*time_difference_in_hours;
    }
    else
        totalAmpHoursUsed_=initial_amountof_amphours_used;


    //isCharging
    if (present_batterycurrent>0)

        isCharging_= false;

        else if (present_batterycurrent<0)

            isCharging_= true;


    //Time of Charging or Depletions

    double time_in_hours;
    int hours;
    int minutes;
    int seconds;
    int milliseconds;
     if(isCharging())
     {
        time_in_hours=abs(totalAmpHoursUsed()/present_batterycurrent);

     }
     else
     {
         time_in_hours=(BATTERY_AMP_HOUR_CAPACITY-totalAmpHoursUsed())/present_batterycurrent;

     }
     while (time_in_hours>24) {
         time_in_hours-=24;
     }

     hours= (int)time_in_hours;
     minutes= (int)((time_in_hours-hours)*60);
     seconds=(int)((((time_in_hours-hours)*60)-minutes)*60);
     milliseconds=(int) ((((((time_in_hours-hours)*60)-minutes)*60)-seconds)*1000);

     QTime n(hours, minutes, seconds, milliseconds);
     timeWhenChargedOrDepleted_=n;



}
