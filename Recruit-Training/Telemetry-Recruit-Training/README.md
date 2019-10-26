## Development server

Run `ng serve` for a dev server. Navigate to `http://localhost:4200/`. The app will automatically reload if you change any of the source files.

## Code scaffolding

Run `ng generate component component-name` to generate a new component. You can also use `ng generate directive|pipe|service|class|guard|interface|enum|module`.

## Build

Run `ng build` to build the project. The build artifacts will be stored in the `dist/` directory. Use the `--prod` flag for a production build.

## Running unit tests

Run `ng test` to execute the unit tests via [Karma](https://karma-runner.github.io).

## Running end-to-end tests

Run `ng e2e` to execute the end-to-end tests via [Protractor](http://www.protractortest.org/).

## Further help

To get more help on the Angular CLI use `ng help` or go check out the [Angular CLI README](https://github.com/angular/angular-cli/blob/master/README.md).





= U of C Solar Car Telemetry Recruit Training

Intro project to learn Angular, 

== Running the project

=== Via Command Line

To run this project on Linux locally, navigate to the source directory and run the following commands:

[source,bash]
----
ng serve
----

== Objective

The goal of this project is to give new recruits a good starting point to learn the required skills to work on the other projects. 
If you ever need any help with how to use Qt's functions, a good start would be to look at http://doc.qt.io/qt-5.6/reference-overview.html[Qt's reference manual]. 
Another useful resource can be found at https://doc.qt.io/qt-5/qtcore-module.html#namespaces. 
This lists and explains how to implement Qt core C++ classes, some of which (i.e. QTime) will need to be used to complete the training tasks. 
Refer to the development resources folder for the style guide. 
In this document you can find the stylistic conventions that are to be used throughout the program.
This project will give recruits a introduction to how the telemetry server works.
By completing this training, recruits can develop the skills required to work on the telemetry server.
This project requires recruits to implement 


=== Tasks to Complete

 *  Change the stylystic elements of the page. 
You can do this in many different ways such as changing the layout of the page, changing the colour scheme, changing fonts, etc. 
The changes made are entirely up to you.
 *  Create a new tab called ` `.
This can be done by
 *  In ``, make a section called ``.
In `` the ___ data must be shown.
The calculations for these values are listed below.
 *  In ``, make another section called ``.
In `` the ___ data must be shown.
The calculations for these values are listed below.

=== Values and Calculations to Note

 *  Refer to `BatteryStateOfChargeService.h` for the function descriptions.
 *  In order to determine whether the battery is charging or depleting, the battery's current must be considered. 
A positive current implies that the battery is charging whereas a negative current means that the battery is depleting. 
 *  The initial amount of Amphours used can be calculated by multiplying the battery's amphour capacity (Ah) by the battery's state of charge (%).
 *  In order to calculate the amphours used between two data points, the average current (A) can be multiplied by the difference in time (h).
 *  The time until the battery is charged can be calculated by dividing the amphours used (Ah) by the current (A). 
The time until depletion can be calculated by dividing the remaining amphours (Ah) by the current.
