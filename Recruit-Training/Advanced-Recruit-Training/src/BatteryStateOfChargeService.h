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

    /*Returns true if the battery is being charged, false if not.*/
    bool isCharging() const;

    /*Return the time remaining to when the battery is charged or depleted*/
    QTime timeWhenChargedOrDepleted() const;

    /*Update Variables*/
    void addData(const BatteryData& batteryData);

private:
    const double initialStateOfChargePercent_;
    double previousCurrent_;
    double previousVoltage_;
    QTime previousTime_;
    double newCurrent_;
    double newVoltage_;
    QTime newTime_;
    double changeInAmpHours_;
    double totalAmpHoursUsed_;
    double averageCurrent_;
    double changeInTime_;
    bool firstRun_;
};
