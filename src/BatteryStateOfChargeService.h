#pragma once

#include "I_BatteryStateOfChargeService.h"
#include "BatteryData.h"

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
    QTime myTime;
    QTime *prevTime;
    double myVoltage;
    double myCurrent;

    // Recommend adding necessary variables here
};
