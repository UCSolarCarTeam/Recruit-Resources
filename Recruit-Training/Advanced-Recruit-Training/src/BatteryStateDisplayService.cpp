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
    /*Calculating the total amount of hour through adding the overlapHours stored in the milisecond space
      to the the hours space*/
    batteryStateOfChargeService_.addData(batteryData);
    QTextStream(stdout) << "Voltage: " << batteryData.voltage
                        << " Current: " << batteryData.current
                        << " Total Ah used: "
                        << batteryStateOfChargeService_.totalAmpHoursUsed() << endl;



    if (batteryStateOfChargeService_.isCharging())
    {
        QTextStream(stdout) << "Time until fully charged: ";

    }
    else
    {
        QTextStream(stdout) << "Time until fully depleted: ";
    }

    QTextStream(stdout) << batteryStateOfChargeService_.hoursInteger
                        << ":"
                        << batteryStateOfChargeService_.timeWhenChargedOrDepleted().minute()
                        << ":"
                        << batteryStateOfChargeService_.timeWhenChargedOrDepleted().second()
                        << ":" << batteryStateOfChargeService_.timeWhenChargedOrDepleted().msec()
                        << "\n" << endl;
}
