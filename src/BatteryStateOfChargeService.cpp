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
#include <stdio.h>

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int HOURS_TO_MSECS = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    ampHourTotal_ = (initialStateOfChargePercent_/100) * BATTERY_AMP_HOUR_CAPACITY;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHourUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(currCurrent_ >= 0)
    {
        return false;
    }
    return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double ampHoursLeft;
    int current = currCurrent_;
    if(isCharging())
    {
        ampHoursLeft = BATTERY_AMP_HOUR_CAPACITY - ampHourTotal_;
        current *= -1;
    }
    else
    {
        ampHoursLeft = ampHourTotal_;
    }
    double msecLeft = (ampHoursLeft * HOURS_TO_MSECS) / current;
    QTime timeLeft = QTime(0,0,0,0).addMSecs(msecLeft);
    return timeLeft;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if(currTime_.isNull())
    {
        prevTime_ = QTime(0,0,0,0);
    }
    prevCurrent_ = currCurrent_;
    currCurrent_ = batteryData.current;
    prevTime_ = currTime_;
    currTime_ = batteryData.time;

    //ampHourCalculation is put here instead of totalAmpHoursUsed() due to the method being a const
    double diffOfTime = (double)prevTime_.msecsTo(currTime_)/HOURS_TO_MSECS;
    double avgCurrent = (currCurrent_+prevCurrent_)/2;

    double changeInAmpHour = avgCurrent * diffOfTime;
    ampHourTotal_ += changeInAmpHour;
    ampHourUsed_ = BATTERY_AMP_HOUR_CAPACITY- ampHourTotal_;
}
