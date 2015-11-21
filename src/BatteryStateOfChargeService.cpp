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
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
, previousCurrent_(0)
{
    ampHours_ = (BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_) / 100;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY - ampHours_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if(previousCurrent_ < 0)
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
    double timeRemaining = (BATTERY_AMP_HOUR_CAPACITY-ampHours_) / previousCurrent_;
    timeRemaining = qAbs(timeRemaining) / MILLISECONDS_TO_HOURS;
    return QTime(0, 0, 0, 0).addMSecs(timeRemaining);
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double presentCurrent = batteryData.current;
    if(previousCurrent_ == 0)
    {
        avgCurrent_ = presentCurrent;
    }
    else
    {
        avgCurrent_ = (previousCurrent_ + presentCurrent) / 2;
    }

    newTime_ = batteryData.time;
    deltaTime_ = previousTime_.msecsTo(newTime_);

    deltaTime_ = deltaTime_ * MILLISECONDS_TO_HOURS;

    double deltaAmpHours = avgCurrent_ * deltaTime_;
    ampHours_ += deltaAmpHours;

    previousTime_ = newTime_;
    previousCurrent_ = presentCurrent;
}
