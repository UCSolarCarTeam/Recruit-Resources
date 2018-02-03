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
        if(batteryStateOfChargeService_.isCharging())
        {
           QTextStream(stdout) <<"Time until charged:" <<batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString("hh:mm:ss.zzz") <<"\n";
        }
        else{
          QTextStream(stdout)  <<" Time until depletion:" <<batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString("hh:mm:ss.zzz") << "\n";
        }
}
