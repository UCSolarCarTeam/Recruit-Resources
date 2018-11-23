#include "BatteryData.h"

BatteryData::BatteryData()
: time()
, voltage(0.0)
, current(0.0)
{
}

BatteryData::BatteryData(QTime t, double v, double c)
: time(t)
, voltage(v)
, current(c)
{
}

BatteryData::~BatteryData()
{
}


QTime BatteryData::GetTime()
{
    return time;
}

double BatteryData::GetVoltage()
{
    return voltage;
}

double BatteryData::GetCurrent()
{
    return current;
}
