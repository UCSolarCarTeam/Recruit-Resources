#pragma once

#include "BatteryData.h"
#include "I_BatteryStateOfChargeService.h"

struct BatteryData;

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
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;

    // Add your necessary variables here
    double latestCurrent_;
    QTime  latestTime_;
    double ampHoursUsed_;
    bool   containsData_;
};
