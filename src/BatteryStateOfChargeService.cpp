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
#include "BatteryData.h"
 
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MSECS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, presentCurrent_(0)
, firstRun_(true)
{
    ampHoursUsed_ = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_ / 100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return ampHoursUsed_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(presentCurrent_ >= 0)
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
    double timeLeft;
    timeLeft=qAbs(ampHoursUsed_ / presentCurrent_) / MSECS_TO_HOURS;
    QTime base(0,0);
    return base.addMSecs(timeLeft);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
 
    double previousCurrent_ = presentCurrent_;
    QTime previous_Time = presentTime_;

    presentCurrent_ = batteryData.current;
    presentTime_ = batteryData.time;

    if(firstRun_ != false)
    {
        firstRun_ = false;
    }
    else
    {
        int msSinceLastTime = abs(previous_Time.msecsTo(presentTime_));
        double hoursSinceLastTime = msSinceLastTime * MSECS_TO_HOURS;

        double avgCurrent = (presentCurrent_ + previousCurrent_) / 2;

        double ampHoursBetweenPresentPreviousTime = avgCurrent * hoursSinceLastTime;

        ampHoursUsed_ = ampHoursUsed_ - ampHoursBetweenPresentPreviousTime;
    }
}
