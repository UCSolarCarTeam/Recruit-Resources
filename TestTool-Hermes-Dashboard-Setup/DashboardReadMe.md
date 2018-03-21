# Epsilon-Dashboard

The Epsilon Dashboard displays information on the screens.

## Switching Modes

There are three different modes for the dashboard: Display mode, Debug Display mode and race mode. The default mode is display mode.
To run the application in different modes, navigate to the directory where you made the executable file for the dashboard. 

To run the application in display mode, run the command:
	`./EpsilonDashboard`

To run the application in debug display mode, run the command:
	`./EpsilonDashboard -d`
  
To run the application in race mode, add the -r flag at the end:
  `./EpsilonDashboard -r`

## Setting up Rabbitmq

In this repo, there are dependencies needed for Rabbitmq before you will be able to build or run anything.

To install these dependencies, run the command:
	`./EpsilonDashboardSetup.sh`
