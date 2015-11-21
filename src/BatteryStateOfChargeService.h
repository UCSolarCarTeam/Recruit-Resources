#pragma once

#include "I_BatteryStateOfChargeService.h"
#include "LogFileReader.h"


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

    QTime previousTime_;
    QTime newTime_;
    double previousCurrent_;
    double deltaTime_;
    double avgCurrent_;
    double ampHours_;
};
