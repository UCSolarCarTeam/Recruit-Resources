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
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), newCurrent(0)
{
    ampHours = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-ampHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newCurrent<0)
        return false;
    else
        return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double timeLeft;


    timeLeft = (BATTERY_AMP_HOUR_CAPACITY-ampHours)/newCurrent;
    timeLeft = timeLeft/MILLISECONDS_TO_HOURS;
    timeLeft = qAbs(timeLeft);

     QTime baseTime (0, 0, 0, 0);
     QTime timeLeftTillDepletionorCharge;
     timeLeftTillDepletionorCharge = baseTime.addMSecs(timeLeft);

    return timeLeftTillDepletionorCharge;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{



    double timeChange;
    double changeInAmpHours;
    QTime previousTime;


    previousCurrent = newCurrent;
    newCurrent = batteryData.current;
     if (previousCurrent == 0) //For the very first line of data
         averageCurrent = newCurrent;
     else
        averageCurrent = (previousCurrent+newCurrent)/2;


    previousTime = newTime;
    newTime = batteryData.time;
    timeChange =previousTime.msecsTo(newTime);
    timeChange = timeChange * MILLISECONDS_TO_HOURS ;

    changeInAmpHours = averageCurrent * timeChange;
    ampHours +=  changeInAmpHours;


}

