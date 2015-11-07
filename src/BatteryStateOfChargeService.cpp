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
#include <QFile>
#include <QString>
#include <QTextStream>
#include "LogFileReader.h"

namespace
{
    const double BATTERY_AMP_HOUR_CAPACITY = 123.0;
    const double MILLISECONDS_TO_HOURS = 2.77778e-7;
}

BatteryStateOfChargeService::BatteryStateOfChargeService(double initialStateOfChargePercent)
: initialStateOfChargePercent_(initialStateOfChargePercent), NewCurrent(0)
{
    AmpHours = BATTERY_AMP_HOUR_CAPACITY * (initialStateOfChargePercent_/100);
}

BatteryStateOfChargeService::~BatteryStateOfChargeService()
{
}

double BatteryStateOfChargeService::totalAmpHoursUsed() const
{
    return BATTERY_AMP_HOUR_CAPACITY-AmpHours;
}

bool BatteryStateOfChargeService::isCharging() const
{
    if (NewCurrent<0)
        return false;
    else
        return true;
}

QTime BatteryStateOfChargeService::timeWhenChargedOrDepleted() const
{
    double TimeLeft;
    double Hours;
    double Minutes;
    double Seconds;
    double SumCurrent = 0;
    double counter;

    counter++;

     double TotalAverageCurrent;



    SumCurrent += InitialCurrent;

    TotalAverageCurrent = SumCurrent/counter;

    TimeLeft = (BATTERY_AMP_HOUR_CAPACITY-AmpHours)/TotalAverageCurrent;

    TimeLeft = qAbs(TimeLeft);


    Hours = TimeLeft;
    int h = (int)TimeLeft;

    Minutes = (Hours-h)*60;
    int m = (int)Minutes;

    Seconds = (Minutes-m)*60;
    int s = (int)Seconds;

    int ms = (Seconds-s)*1000;

    QTime time(h, m, s, ms);


    return time;
}

void BatteryStateOfChargeService::addData(const BatteryData& batteryData)
{



    double TimeChange;
    double AmpHChange;

     QTime InitialTime;


    InitialCurrent = NewCurrent;
    NewCurrent = batteryData.current;
     if (InitialCurrent == 0)
         AverageCurrent = NewCurrent;
     else
        AverageCurrent = (InitialCurrent+NewCurrent)/2;


    InitialTime = NewTime;
    NewTime = batteryData.time;
    TimeChange =InitialTime.msecsTo(NewTime);
    TimeChange = TimeChange * MILLISECONDS_TO_HOURS ;

    AmpHChange = AverageCurrent * TimeChange;
    AmpHours +=  AmpHChange;


}

