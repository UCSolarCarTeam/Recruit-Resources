# U of C Solar Car Advanced Recruit Training
Intro project to learn c++ and QT

To build this project on linux navigate to the source directory and run the following commands:

`qmake`

`make`

To run the project:
`./batteryLife` - Refer to help for further instructions

In QT Creator, the above `qmake` and `make` are located in `Build`, and the project can be run through the play button. You'll have to set the appropriate command line arguments in `Projects > Build & Run > Run`. 

The goal of this project is to give new recuits a good starting point to learn the required skills to work on the other projects. 
If you ever need any help with how to use Qt's functions, a good start would be to look at the [Qt's reference manual](http://doc.qt.io/qt-5.6/reference-overview.html)

Tasks to complete:
 *  Complete the error checking in LogFileReader.
 *  Implement the functions of BatteryStateOfChargeService.
 *  Print out time until depleted or charged in BatteryStateDisplayService.

Values to note for the BatteryStateOfChargeService:
 *  The battery is charging when the battery current is negative, depleting when it is positive.
 *  The initial amount of Amphours used would be the Battery's Amphour capacity(Ah) x it's state of charge(%).
 *  The change in amphours used between two data points would be the average current(A) x the difference in time(h)
 *  The time until charge would be the Amphours used(Ah) divided by the current (A). Similarily, the time until depletion would be the remaining amphours divided by the current.    