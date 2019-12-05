#include <QTextStream>

#include "BatteryData.h"
#include "BatteryStateDisplayService.h"
#include "I_BatteryDataSource.h"
#include "I_BatteryStateOfChargeService.h"

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
    batteryStateOfChargeService_.addData(batteryData);

    QTextStream(stdout) << "Voltage: " << batteryData.voltage
        << " Current: " << batteryData.current
        << " Total Ah used: " << batteryStateOfChargeService_.totalAmpHoursUsed();

    // TODO: Print out time until the battery is fully charged or depleted.    
    int milliseconds = batteryStateOfChargeService_.timeWhenChargedOrDepleted().msec();
    QString zeroPlaceholder;

    if(milliseconds < 100)
        zeroPlaceholder = "0";
    else if(milliseconds < 10)
        zeroPlaceholder = "00";

    if(batteryStateOfChargeService_.isCharging())
        QTextStream(stdout) << " Time until charged: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << "." << zeroPlaceholder << milliseconds <<endl;
    else
        QTextStream(stdout) << " Time until depleted: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << "." << zeroPlaceholder << milliseconds << endl;
}
