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

BatteryData& BatteryData::operator= (const BatteryData& rhs)
{
    if(this != &rhs)
    {
        time = rhs.time;
        voltage = rhs.voltage;
        current = rhs.current;
    }
    return *this;
}
