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
    const int SECONDS_TO_MILISECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    initialAmpUsed_ = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent / 100;
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return totalAmpUsed_;
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
    double newTimeSecs = QTime(0,0,0).secsTo(newTime_);
    double TimeElapsed =(BATTERY_AMP_HOUR_CAPACITY / fabs(newCurrent_)) * SECONDS_TO_HOURS;
    newTimeSecs = newTimeSecs + TimeElapsed;
    QTime estimatedTime = QTime(0,0,0).addSecs(newTimeSecs);

    return estimatedTime;
}
void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    newTime_ = batteryData.time;
    newCurrent_ = batteryData.current;

    double TimeUsed = newTime_.msecsTo(oldTime_);
    double averageCurrent = (newCurrent_ + oldCurrent_) / 2;
    totalAmpUsed_ = initialAmpUsed_ + averageCurrent  / (TimeUsed / SECONDS_TO_MILISECONDS);

    oldTime_ = newTime_;
    oldCurrent_ = newCurrent_;
}
