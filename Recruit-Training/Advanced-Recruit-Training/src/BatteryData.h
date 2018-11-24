#pragma once

#include <QTime>

struct BatteryData
{
    BatteryData();
    BatteryData(QTime t, double v, double c);
    virtual ~BatteryData();

    QTime time;
    QTime prevTime;
    double voltage; // in V note all units should be stored in SI units - Current
    double current; // in A - Current
    double prevCurrent;
};
