/** 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 
 *  of the License, or (at your option) any later version.
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General 
 *  Public License along with the University of Calgary Solar Car 
 *  Team New Recruit Exercise. If not, see 
 *  <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */
#include<QDebug>
#include "BatteryData.h"
#include "BatteryStateOfChargeService.h"
#include <QTime>
#include <math.h>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int SECONDS_TO_HOURS = 3600;
    const int SECONDS_TO_MINUTUES = 60;

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
    return totalcurrent_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newcurrent_ <= 0)
    {   return true;}
    else
    {   return false;}
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return estimatetime_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{   
    newcurrent_ = batteryData.current;
    double oldcurrent = 0;
    QTime newtime = batteryData.time;
    QTime oldtime = newtime;
    double s1 = QTime(0,0,0).secsTo(newtime);
    double s2 = QTime(0,0,0).secsTo(oldtime);
    int timeused = s1 - s2;
    totalcurrent_ = newcurrent_ - oldcurrent;
    double avg = (fabs(newcurrent_)+fabs(oldcurrent)) * SECONDS_TO_HOURS / timeused;
    int timeNeeded =(BATTERY_AMP_HOUR_CAPACITY - newcurrent_)* SECONDS_TO_HOURS / avg;
    s1 = s1 + timeNeeded;
    int h = s1 / SECONDS_TO_HOURS;
    int m = (s1 - (h * SECONDS_TO_HOURS)) / SECONDS_TO_MINUTUES;
    int s = s1 - (h * SECONDS_TO_HOURS) - (m * SECONDS_TO_MINUTUES);
    estimatetime_ = QTime(h,m,s);
    oldtime = newtime;
    oldcurrent=newcurrent_;
}
