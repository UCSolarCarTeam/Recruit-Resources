/** 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *  Copyright (C) 2015 University of Calgary Solar Car Team
 *
 *  This file is part of the 
 *  University of Calgary Solar Car Team New Recruit Exercise
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is free software: you can redistribute it and/or modify it 
 *  under the terms of the GNU General Public License as 
 *  published by the Free Software Foundation, either version 3 
 *  of the License, or (at your option) any later version.
 *
 *  The University of Calgary Solar Car Team New Recruit Exercise 
 *  is distributed in the hope that it will be useful, but WITHOUT 
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General 
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General 
 *  Public License along with the University of Calgary Solar Car 
 *  Team New Recruit Exercise. If not, see 
 *  <http://www.gnu.org/licenses/>.
 *
 *  For further contact, email <software@calgarysolarcar.ca>
 */

#include <QCommandLineParser>
#include <QCoreApplication>
#include <QTimer>

#include "BatteryStateDisplayService.h"
#include "BatteryStateOfChargeService.h"
#include "LogFileReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Battery Life Predictor");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption filenameOption(QStringList() << "f" << "filename",
            QCoreApplication::translate("main", "Name of csv log file of battery data"),
            QCoreApplication::translate("main", "filename"));
    parser.addOption(filenameOption);

    QCommandLineOption initialStateOfChargeOption(QStringList() << "i" << "initStateOfCharge",
            QCoreApplication::translate("main", "Initial State Of Charge of Battery as percent from 0-100"),
            QCoreApplication::translate("main", "stateOfCharge"));
    parser.addOption(initialStateOfChargeOption);

    parser.process(app);

    QString filename = parser.value(filenameOption);
    QString initialStateOfChargeString = parser.value(initialStateOfChargeOption);
    if (filename.isNull() || initialStateOfChargeString.isNull())
    {
        parser.showHelp();
        return -1;
    }
    double initialStateOfCharge = initialStateOfChargeString.toDouble();

    LogFileReader logFileReader;
    BatteryStateOfChargeService batteryStateOfChargeService(initialStateOfCharge);
    BatteryStateDisplayService batteryStateOfChargeDisplayService(logFileReader, batteryStateOfChargeService);

    logFileReader.readAll(filename);

    // Quit the program when it is done.
    QTimer::singleShot(0, &app, SLOT(quit()));
    return app.exec();
};
