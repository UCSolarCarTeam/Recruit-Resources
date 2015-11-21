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
    double objectCurrent;
    double inCurrent=0;
    double changeTime;
    double inVoltage;
    double Voltage;
    QTime initialTime;
    QTime currentTime;
    double AmpHours;
    double Current;
    int counter;
    double SumCurrent=0;
    double TimeLeft;
    double AverageCurrent;
    double Hours;
    double Minutes;
    double Seconds;
    double Milliseconds;
    QTime t;
    double AmpChange;
    double dTime;
    // Recommend adding necessary variables here
};
