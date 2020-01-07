#include <QTextStream>
#include <QTime>
#include <QString>

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

    double millisec = batteryStateOfChargeService_.timeWhenChargedOrDepleted().msec();

    QString numberMillisec = QString("%1").arg((int)(millisec), 3, 10, QChar('0'));

    QTextStream(stdout) << "Voltage: " << batteryData.voltage
        << " Current: " << batteryData.current
        << " Total Ah used: " << batteryStateOfChargeService_.totalAmpHoursUsed();
    if(batteryStateOfChargeService_.isCharging())
    {
        QTextStream(stdout) << " Time until charged: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() <<"."
                            << numberMillisec << endl;
    }
    else
    {
        QTextStream(stdout) << " Time until depleted: " << batteryStateOfChargeService_.timeWhenChargedOrDepleted().toString() << "."
                            << numberMillisec << endl;
    }

}
