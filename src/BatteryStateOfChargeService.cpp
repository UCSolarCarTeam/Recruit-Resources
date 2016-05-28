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
namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const int SECONDS_TO_HOURS = 3600;
    const int SECONDS_TO_MILLISECONDS = 1000;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent)
{
    double initialampused = BATTERY_AMP_HOUR_CAPACITY * initialStateOfChargePercent / 100;
    totalAmpUsed_ = initialampused;
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
    if (newCurrent_ < 0)
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
    double seconds = QTime(0,0,0).secsTo(newTime_);
    double timeElapsed =(BATTERY_AMP_HOUR_CAPACITY / fabs(newCurrent_)) * SECONDS_TO_HOURS;
    seconds += timeElapsed;
    QTime estimatedTime = QTime(0,0,0).addSecs(seconds);
    return estimatedTime;
}
void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    QTime oldTime = newTime_;
    if (oldTime.isNull())
    {
        oldTime = QTime(0,0,0);
    }

    double oldcurrent = newCurrent_;
    newTime_ = batteryData.time;
    newCurrent_ = batteryData.current;

    double timeused = newTime_.msecsTo(oldTime);
    double averagecurrent = (newCurrent_ + oldcurrent) / 2;
    totalAmpUsed_ += averagecurrent  / (timeused / SECONDS_TO_MILLISECONDS);
}
