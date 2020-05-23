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
    double OldCurrent_;
    double PresentBatteryCurrent_;
    double TotalAmpHoursUsed_;
    bool IsCharging_;
    QTime TimeWhenChargedOrDepleted_;
    QTime OldTime_;
    QTime PresentTime_;
};
