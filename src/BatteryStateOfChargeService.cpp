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


namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_SEC = 3600000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    totalAmpHours_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent_ / 100;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    if (totalAmpHours_ > BATTERY_AMP_HOUR_CAPACITY)
    {
        return 0;
    }
    else if (totalAmpHours_ < 0)
    {
        return BATTERY_AMP_HOUR_CAPACITY;
    }
    else
    {
        return BATTERY_AMP_HOUR_CAPACITY - totalAmpHours_;
    }
}

bool BatteryStateOfChargeService::isCharging() const
{
    return previousCurrent_ < 0;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    if (returnTime_.isNull() || totalAmpHours_ > BATTERY_AMP_HOUR_CAPACITY)
    {
        return QTime(0, 0);
    }
    else
    {
        return returnTime_;
    }
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    double deltaAmpHours;

    if (previousTime_.isNull())
    {
        previousTime_ = batteryData.time;
    }
    deltaTime_ = previousTime_.msecsTo(batteryData.time) / HOUR_TO_SEC;
    averageCurrent_ = (batteryData.current + previousCurrent_) / 2;
    totalAmpHours_ += (deltaTime_ * averageCurrent_);

    if (batteryData.current < 0)
    {
        deltaAmpHours = -1 * (BATTERY_AMP_HOUR_CAPACITY - totalAmpHours_);
    }
    else
    {
        deltaAmpHours = totalAmpHours_;
    }

    returnTime_ = QTime(0, 0).addMSecs((deltaAmpHours / batteryData.current) * HOUR_TO_SEC);

    previousTime_ = batteryData.time;
    previousCurrent_ = batteryData.current;
}
