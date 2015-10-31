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

    double InitialCurrent;
    double CurrentPrime = 0;
    double AmpHours;
    double AmpHChange;
    double AverageCurrent;
    QTime InitialTime;
    QTime TimePrime;
    QTime t;
    double TimeLeft;
    double TimeChange;
    double TimeRemaining;
    double HoursPrime;
    double MinutesPrime;
    double SecondsPrime;
    double AverageCurrentPrime;
    double NewCurrent = 0;
    int counter;

};
