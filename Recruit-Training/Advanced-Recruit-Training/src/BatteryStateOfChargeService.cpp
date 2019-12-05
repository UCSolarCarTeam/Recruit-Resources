#include "BatteryStateOfChargeService.h"
#include "BatteryData.cpp"
#include <QTime>
#include <QLocale>
#include <cmath>
#include <QTextStream>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;

   // double n = 0; //running total from somewhere...
    //double totalCurrent = 0;
    //:double averageCurrent = 0;

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

    return totalAmphoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(current_ < 0){
        return true;
    }
    return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
   /* //time until battery is charged = amphours used (Ah)/current (A)
    //double time_until_charged = batteryStateOfChargeService_.totalAmpHoursUsed()/batteryData.current;
    // time until battery is depleted = remaining amphours (Ah)/current(A)
    double timeUntilCharged;
    if(isCharging()){
        //time until battery is charged
        timeUntilCharged = totalAmpHoursUsed()/current_ * -1;
    }else{
        timeUntilCharged = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_;
    }
        int hourCharged = (int) floor(timeUntilCharged);
        double minute = (timeUntilCharged - hourCharged) * 60;
        int minuteCharged = (int) floor(minute);
        double seconds = (minuteCharged - minute) * 60;
        int secondsCharged = (int) floor(seconds);
        double millisec = (secondsCharged - seconds) * 1000;
        int millisecCharged = (int) floor(millisec);

        //QString time = QString::number(timeUntilCharged);
        //QTextStream(stdout) << "time:" << time << endl;

        QTime time(hourCharged, minuteCharged, secondsCharged, millisecCharged);
         //double timeUntilDepleted = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed())/current_;
        return time;
       //time until battery is depleted

//        QString time = QString::number(timeUntilDepleted);
//        return QTime::fromString(time, "hh:mm:ss.zzz");

    //return QTime::currentTime();
*/
    double totalHoursRemaining, msRemaining;
        int h, m, s, ms;

        if(isCharging())
            totalHoursRemaining = totalAmpHoursUsed() / current_ * -1;
        else
            totalHoursRemaining = (BATTERY_AMP_HOUR_CAPACITY - totalAmpHoursUsed()) / current_;

        while(totalHoursRemaining > 24){
            totalHoursRemaining -= 24;
        }
        //Converting totalHoursRemaining into h, m, s, ms
        h = totalHoursRemaining;

        msRemaining = (totalHoursRemaining - h) * 3600000;
        m = msRemaining / 60000;
        msRemaining = msRemaining - (m * 60000);
        s = msRemaining / 1000;
        msRemaining = msRemaining - (s * 1000);
        ms = msRemaining;

        QTime timeRemaining(h, m, s, ms);
        return timeRemaining;

}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double initialAmphoursUsed = (initialStateOfChargePercent_ * BATTERY_AMP_HOUR_CAPACITY)/100;
    Q_UNUSED(batteryData)
    // This is where you can update your variables
    // Hint: There are many different ways that the totalAmpHoursUsed can be updated
    // i.e: Taking a running average of your data values, using most recent data points, etc.

    oldCurrent_ = current_;
    current_ = batteryData.current;
    oldTime_ = newTime_;
    newTime_ = batteryData.time;
    double averageCurrent = (oldCurrent_ + current_)/2;

    double changeInTimeMseconds = oldTime_.msecsTo(newTime_);
    //use secsTo to get the number of seconds elasped from old to new?
    double seconds = changeInTimeMseconds/1000;
    double hour = seconds/3600;
    currentAmphoursUsed_ = (hour * averageCurrent);
    totalAmphoursUsed_ = totalAmphoursUsed_ + currentAmphoursUsed_ + initialAmphoursUsed ; //need to include the totalcurrent again and maybe initialize totalAmphoursUsed to be the intitialAmphoursUsed instead ...
    //totalAmphoursUsed_ = averageCurrent;

    if(totalAmphoursUsed_ != initialAmphoursUsed){
        totalAmphoursUsed_ = totalAmphoursUsed_ - initialAmphoursUsed;
    }
    //then use that to turn it into hours and then multiply it to the current
    //then you get your amphours used
    //then keep on adding onto the amphours
    //in the amphours method, just return the instance variable amphours
    //amphours used between 2 data points = average current(A) * difference in time (h)


}
