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
    return totalcurrent;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newcurrent<=0)
        qDebug()<<"is charging";
    else
        return false;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return et;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{   
    newcurrent = batteryData.current;
    newtime = batteryData.time;
    s1 = QTime(0,0,0).secsTo(newtime);
    s2 = QTime(0,0,0).secsTo(oldtime);
    timeused = s1-s2;
    totalcurrent = newcurrent - oldcurrent;
    double avg = (fabs(newcurrent)+fabs(oldcurrent)) *3600 / timeused;
    int tneed =(BATTERY_AMP_HOUR_CAPACITY - newcurrent)*3600/avg;
    s1 = s1 + tneed;
    int h = s1/3600;
    int m = (s1 - (h*3600))/60;
    int s = s1 - (h*3600)-(m*60);
    et = QTime(h,m,s);
    oldtime = newtime;
    oldcurrent=newcurrent;
    Q_UNUSED(batteryData);
    // Update your variables here.
}
