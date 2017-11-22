#pragma once

#include "I_BatteryStateOfChargeService.h"

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
    double current_ = 0;
    double previousCurrent_ = 0;
    QTime time_;
    QTime previousTime_;
    double additionalAmpHours_ = 0;
    double totalAmpHours_ = 0;

};
