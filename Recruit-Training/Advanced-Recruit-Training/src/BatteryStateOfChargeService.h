#pragma once

#include "I_BatteryStateOfChargeService.h"
#include "BatteryData.h"

class BatteryStateOfChargeService : public I_BatteryStateOfChargeService
{
public:
    explicit BatteryStateOfChargeService(double initialStateOfChargePercent);
    virtual ~BatteryStateOfChargeService();

    /*Returns the total amp hours used*/
    double totalAmpHoursUsed() const;

    /* The battery is charging if the battery current is negative
     * The battery is depleting if the battery current is positive
     * Returns true if the battery is being charged, false if not.*/
    bool isCharging() const;

    /* Amphours used (Ah) divided by the current (A) is the time until charged
     * Remaining Amphours (Ah) divided by the current (A) is the time until depletion
     * Return the time remaining to when the battery is charged or depleted*/
    QTime timeWhenChargedOrDepleted() const;

    /*Update Variables*/
    void addData(const BatteryData& batteryData);

private:
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;
    BatteryData data_;
    double remainingAmpHours_;
    bool isFirstRun_;
    double oldCurrent_;
    QTime oldTime_;
    // Add your necessary variables here
};
