#include <QTextStream>

#include "BatteryData.h"
#include "BatteryStateDisplayService.h"
#include "I_BatteryDataSource.h"
#include "I_BatteryStateOfChargeService.h"

namespace
{
  const double MAX_AMP_HOURS = 123.0;
}
BatteryStateDisplayService::BatteryStateDisplayService(
    const I_BatteryDataSource& batteryDataSource,
    I_BatteryStateOfChargeService& batteryStateOfChargeService)
: batteryStateOfChargeService_(batteryStateOfChargeService)
{
    // This function is what "connects" the signal to the slot. So whenever the
    // signals it emitted, the slot will be called and the signal arguements
    // will be passed into the slot.
    connect(&batteryDataSource, SIGNAL(batteryDataReceived(const BatteryData&)),
        this, SLOT(handleBatteryDataReceived(const BatteryData&)));
}

BatteryStateDisplayService::~BatteryStateDisplayService()
{
}

void BatteryStateDisplayService::handleBatteryDataReceived(const BatteryData& batteryData)
{
    if (batteryStateOfChargeService_.totalAmpHoursUsed() < MAX_AMP_HOURS)
    {
        batteryStateOfChargeService_.addData(batteryData);
        QString temp;
        if (batteryStateOfChargeService_.isCharging())
          temp = ", Time until charged: ";
        else
          temp = ", Time until depleted: ";

        QTextStream(stdout) << "Voltage: " << batteryData.voltage_
            << ", Current: " << batteryData.current_
            << ", Total Ah used: " << batteryStateOfChargeService_.totalAmpHoursUsed()
            << temp << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << endl;
    }
}
