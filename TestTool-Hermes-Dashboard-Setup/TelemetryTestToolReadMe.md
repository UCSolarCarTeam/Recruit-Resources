# University of Calgary Solar Car Team Schulich Delta Telemetry Test Tool

Test tool to mock out the serial telemetry protocol defined in https://docs.google.com/spreadsheets/d/1soVLjeD9Sl7z7Z6cYMyn1fmn-cG7tx_pfFDsvgkCqMU/edit#gid=0.

TelemetryTestTool requires SimpleAmpClient and RabbitMQ both fully configured to properly test the program. 

To use, create a pair of virtual com ports and connect with this program and the one that you are testing.

## Linux
You can test socat to create Virtual Serial Port doing the following procedure:

Open a terminal (let's call it Terminal 0) and execute:

```
socat -d -d pty,raw,echo=0 pty,raw,echo=0`
```

The code above returns:

```
2013/11/01 13:47:27 socat[2506] N PTY is /dev/pts/2
2013/11/01 13:47:27 socat[2506] N PTY is /dev/pts/3
2013/11/01 13:47:27 socat[2506] N starting data transfer loop with FDs [3,3] and [5,5]
```

The two ports /dev/pts/2 and /dev/pts/3 are now connected.

## Testing
The telemetry test tool uses googletest and googlemock,so the gmock and gtest header files need to be in your include path `/usr/local/include` or `/usr/include`.

If you do not already have the library, you will need to compile it yourself.
Meaning you need a `libgmock.a` archive file in the test directory in order to compile the tests.

To create a `libgmock.a` file in a Linux system, follow these instructions in an arbitrary dir.

1. Get the googletest and googlemock source code:
    `git clone https://github.com/google/googletest.git`

2. Go into the cloned directory:
    `cd googletest/`

3. Compile googletest:
    `g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googletest/src/gtest-all.cc`

4. Compile googlemock:
    `g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googlemock/src/gmock-all.cc`

5. Collect both the resulting .o files into an archive file:
    `ar -rv libgmock.a gtest-all.o gmock-all.o`

You should now have a `libgmock.a` archive file.
Create a `build/.lib` directory using `mkdir -p Location_of_your_local_Test Tool_repository/build/.lib` and then place the `libmock.a` archive file in the new `build/.lib/` directory and you should be good to go.
Use `ls -a` to show all hidden files.

### Start Server

`sudo rabbitmq-server` can be used to start the server on Linux.

### Refresh Server

On linux to refresh the contents of the server perform the following commands:

`rabbitmqctl stop_app`

`rabbitmqctl reset`

`rabbitmqctl start_app`

