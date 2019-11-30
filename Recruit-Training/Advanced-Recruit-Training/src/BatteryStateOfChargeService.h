#pragma once

#include "I_BatteryStateOfChargeService.h"

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

    /*Return the remaining hours due size limit of hours in QTime*/
    int getRemainingHours() const;

    /*Update Variables*/
    void addData(const BatteryData& batteryData);

private:
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;

    // Add your necessary variables here
    //double current_;
    double currentNew_;
    double ampHours_;
    QTime timeNew_;
    QTime timeTillChargeOrDepletion_;
    int remainingHours_;
};
