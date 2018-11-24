#pragma once

#include <QTime>

struct BatteryData
{
    BatteryData();
    BatteryData(QTime t, double v, double c);

    virtual ~BatteryData();

    QTime time_;
    double voltage_; // in V note all units should be stored in SI units
    double current_; // in A
};
