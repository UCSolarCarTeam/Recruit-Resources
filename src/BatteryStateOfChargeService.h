#pragma once

#include "I_BatteryStateOfChargeService.h"

class BatteryStateOfChargeService : public I_BatteryStateOfChargeService
{
public:
    explicit BatteryStateOfChargeService(double initialStateOfChargePercent);
    virtual ~BatteryStateOfChargeService();

    double totalAmpHoursUsed() const;
    bool isCharging() const;
    QTime timeWhenChargedOrDepleted() const;

    void addData(const BatteryData& batteryData);

private:
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;
    double AvgCurrent;
    double inCurrent;
    double changeTime;
    QTime prevTime;
    QTime currentTime;
    double AmpHours;
    double Current;
    double AverageCurrent;
    double dTime;
    double SumCurrent;
    // Recommend adding necessary variables here
};
