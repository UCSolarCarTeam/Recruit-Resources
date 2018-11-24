#pragma once

#include <QObject>
//struct BatteryData;
#include "BatteryData.h"

class I_BatteryDataSource : public QObject
{
    Q_OBJECT
public:
    virtual ~I_BatteryDataSource() {}

signals:
    void batteryDataReceived(const BatteryData& batteryData);
};
