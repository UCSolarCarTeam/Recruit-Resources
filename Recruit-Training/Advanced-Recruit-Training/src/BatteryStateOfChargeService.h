#pragma once

#include "I_BatteryStateOfChargeService.h"
#include <QTime>
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

    const double initialStateOfChargePercent_;
    double oldCurrent_;
    double presentBatteryCurrent_;
    double totalAmpHoursUsed_;
    bool isCharging_;
    QTime timeWhenChargedOrDepleted_;
    QTime oldTime_;
    QTime presentTime_;
};
