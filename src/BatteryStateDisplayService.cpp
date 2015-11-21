#include <QTextStream>
#include "BatteryData.h"
#include "BatteryStateDisplayService.h"
#include "I_BatteryDataSource.h"
#include "I_BatteryStateOfChargeService.h"

namespace
{
    const QString TIME_FORMAT = "hh:mm:ss.zzz";
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
    batteryStateOfChargeService_.addData(batteryData);

    QTextStream(stdout) << "Voltage: " << batteryData.voltage
        << " Current: " << batteryData.current
        << " Total Ah used: " << batteryStateOfChargeService_.totalAmpHoursUsed()<<endl;
    // TODO Print out time till it is depleted or charged.
    if (batteryStateOfChargeService_.isCharging())
    {
        QTextStream(stdout)<<"Time left till full charge: "
        <<batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString(TIME_FORMAT)<<endl;
    }
    else
    {
        QTextStream(stdout)<<"Time left till fully discharged: "
        <<batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString(TIME_FORMAT)<<endl;
    }
    QTextStream(stdout)<<" "<<endl;
}
