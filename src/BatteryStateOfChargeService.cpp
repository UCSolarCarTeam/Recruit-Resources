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
#include <QDebug>
#include "BatteryData.h"
#include "BatteryStateOfChargeService.h"
#include <QTime>
#include <math.h>
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int SECONDS_TO_HOURS = 3600;
    const int SECONDS_TO_MINUTES = 60;

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
    return totalCurrent_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (newCurrent_ <= 0)
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
    return estimatedTime_;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{   

    QTime newTime = batteryData.time;
    QTime oldTime = newTime;
    double new_Time = QTime(0, 0, 0).secsTo(newTime);
    double old_Time = QTime(0, 0, 0).secsTo(oldTime);
    int TimeUsed = new_Time - old_Time;

    newCurrent_ = batteryData.current;
    double oldCurrent = 0;
    totalCurrent_ = newCurrent_ - oldCurrent;
    double Average = (newCurrent_ + oldCurrent) * SECONDS_TO_HOURS / TimeUsed;

    int timeNeeded =(BATTERY_AMP_HOUR_CAPACITY - newCurrent_) * SECONDS_TO_HOURS / Average;
    new_Time = new_Time + timeNeeded;

    int Hour = new_Time / SECONDS_TO_HOURS;
    int Minute = (new_Time - (Hour * SECONDS_TO_HOURS)) / SECONDS_TO_MINUTES;
    int Second = new_Time - (Hour * SECONDS_TO_HOURS) - (Minute * SECONDS_TO_MINUTES);
    estimatedTime_ = QTime(Hour, Minute, Second);

    oldTime = newTime;
    oldCurrent = newCurrent_;
}
