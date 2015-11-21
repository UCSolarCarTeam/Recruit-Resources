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
#include <IOSTREAM>
#include <QTextStream>
#include <QDebug>
using std::cout; using std::endl;

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double HOUR_TO_SEC = 3600000;
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
    if (totalAH_>BATTERY_AMP_HOUR_CAPACITY)
        return 0;
    else if (totalAH_<0)
        return BATTERY_AMP_HOUR_CAPACITY;
    else
        return BATTERY_AMP_HOUR_CAPACITY - totalAH_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return isCharging_;
}


QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime null_time(0,0,0,0);
    if (return_time.isNull())
        return null_time;
    else
        return return_time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if (previousTime_.isNull())
    {
        totalAH_=BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_/100;
        previousTime_=batteryData.time;
    }
    zero_time.setHMS(0,0,0,0);
    deltaTime_=previousTime_.msecsTo(batteryData.time)/HOUR_TO_SEC;
    deltaCurrent_=(batteryData.current+previousCurrent_)/2;
    amph_=deltaTime_*deltaCurrent_;
    totalAH_+=amph_;

    if (batteryData.current < 0){
        isCharging_=true;
        deltaAH_=-1*(BATTERY_AMP_HOUR_CAPACITY-totalAH_);

    }
    else{
        isCharging_=false;
        deltaAH_=totalAH_;
    }
    deltaAH_ /= batteryData.current;
    return_time=zero_time.addMSecs(deltaAH_*HOUR_TO_SEC);

    previousTime_=batteryData.time;
    previousCurrent_=batteryData.current;

}
