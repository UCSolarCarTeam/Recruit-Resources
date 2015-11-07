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

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
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
    return BATTERY_AMP_HOUR_CAPACITY - totalAH_;
}

bool BatteryStateOfChargeService::isCharging() const
{
    return false;
}


QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    QTime ntime(0,0,0,0);
    if (time.isNull())
        return ntime;
    else
        return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{
    if (prTime_.isNull())
    {
        totalAH_=BATTERY_AMP_HOUR_CAPACITY*initialStateOfChargePercent_/100;
        prTime_=batteryData.time;
    }
    bDC_=batteryData.current;
    deltaT_=prTime_.msecsTo(batteryData.time);
    amph_=deltaT_*bDC_/3600000;
    totalAH_+=amph_;

    if (bDC_ < 0){
        isCharging_=true;
        deltaAH_=-1*(BATTERY_AMP_HOUR_CAPACITY-totalAH_);
    }
    else {
        isCharging_=false;
        deltaAH_=totalAH_;
    }
    deltaAH_=(deltaAH_ / bDC_);

    int hours = deltaAH_;
    int min = (deltaAH_-hours)*60;
    int sec =(deltaAH_-hours-(min/60))*60;
    int ms = (deltaAH_-hours-min/60-sec/3600)*1000;
    time.setHMS(hours,min,sec,ms);
    if (hours>24)
        qDebug() <<time<<"\n"<< deltaAH_<<endl;

    prTime_=batteryData.time;
}











