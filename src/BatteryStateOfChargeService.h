#pragma once

#include "I_BatteryStateOfChargeService.h"
#include "BatteryStateOfChargeService.h"
#include <QDebug>
#include <QFile>
#include <QString>
#include <QTextStream>

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
    // Convention is to have an _ after private members
    const double initialStateOfChargePercent_;

    // Recommend adding necessary variables here
    double initialCurrent;
    double newCurrent = 0;
    QTime initialTime;
    QTime newTime;

    double dTime;
    double aveCurrent;
    double dAmpHours;
    double initialampHours;

    double ampHours = aveCurrent*dTime;

};
