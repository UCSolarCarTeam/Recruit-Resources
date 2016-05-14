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
    return totalAmpUsed;
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
    newTime_ = batteryData.time;
    newCurrent_ = batteryData.current;

    double newTimeMSecs = QTime(0, 0, 0).msecsTo(newTime_);
    double oldTimeMSecs = QTime(0, 0, 0).msecsTo(oldTime_);
    double TimeUsed = (newTimeMSecs - oldTimeMSecs) / SECONDS_TO_HOURS;

    int TimeElapsed =(BATTERY_AMP_HOUR_CAPACITY / fabs(newCurrent_));
    newTimeMSecs = newTimeMSecs + TimeElapsed;

    averageCurrent_ = (newCurrent_ + oldCurrent_) / 2;
    AmpUsed = averageCurrent_ / TimeUsed;
    totalAmpUsed = totalAmpUsed + AmpUsed;

    estimatedTime_ = QTime(0,0,0).addSecs(newTimeMSecs);

    oldTime_ = newTime_;
    oldCurrent_ = newCurrent_;
}
