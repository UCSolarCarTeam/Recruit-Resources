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

#include "BatteryStateOfChargeService.h"
#include <iostream>
#include <QTime>
#include <QDebug>
using namespace std;
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY*(initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (Current < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    return t;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{

    QTime currentTime = batteryData.time;
    changeTime = abs(initialTime.msecsTo(currentTime));
    changeTime = changeTime * 2.77778e-7;
    initialTime = currentTime;
    if ((Current > 0 && Current < 10000000000) || Current < 0 )
    {
        inCurrent = Current;
    }
    Current = batteryData.current;
    if (inCurrent == 0)
    {
        objectCurrent = 0;
    }
    else
    {
        objectCurrent = (inCurrent + Current)/2;
    }

    inVoltage = batteryData.voltage;
    Voltage = batteryData.voltage;
    AmpChange = (objectCurrent * changeTime);

    AmpHours += AmpChange;

    counter++;
    SumCurrent += inCurrent;
    AverageCurrent = SumCurrent/counter;
    TimeLeft= (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/AverageCurrent;
    TimeLeft = qAbs(TimeLeft) * 2.77778e-7;



    Hours = TimeLeft;
    int h = (int)TimeLeft;

    Minutes = (Hours-h)*60;
    int m = Minutes;

    Seconds = (Minutes-m)*60;
    int s = Seconds;

    int ms = (Seconds-s)*1000;

    QTime time(h,m,s,ms);
    t =  time;



    // Update your variables here.
}
