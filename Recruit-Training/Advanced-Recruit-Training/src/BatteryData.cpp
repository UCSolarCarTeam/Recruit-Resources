#include "BatteryData.h"

BatteryData::BatteryData()
: time_()
, voltage_(0.0)
, current_(0.0)
{
}

BatteryData::BatteryData(QTime t, double v, double c)
: time_(t)
, voltage_(v)
, current_(c)
{
}

BatteryData::~BatteryData()
{
}
