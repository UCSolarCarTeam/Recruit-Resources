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
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int SH_CONVERT = 3600;
    const int M_CONVERT = 60;

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
    double avg = (fabs(newcurrent_)+fabs(oldcurrent)) * SH_CONVERT / timeused;
    int tneed =(BATTERY_AMP_HOUR_CAPACITY - newcurrent_)* SH_CONVERT / avg;
    s1 = s1 + tneed;
    int h = s1 / SH_CONVERT;
    int m = (s1 - (h * SH_CONVERT)) / M_CONVERT;
    int s = s1 - (h * SH_CONVERT) - (m * M_CONVERT);
    estimatetime_ = QTime(h,m,s);
    oldtime = newtime;
    oldcurrent=newcurrent_;
    // Update your variables here.
}
