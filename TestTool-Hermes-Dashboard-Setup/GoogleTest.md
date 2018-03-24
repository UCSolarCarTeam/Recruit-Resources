#GoogleTest.md

##GoogleTest 

Testing the telemetry test tool and Hermes is done with googletest and google mock 

the gmock and gtest header files need to be in your include path `/usr/local/include` or `/usr/include`.

You must compile the library that has the definitions yourself.
Meaning you need a `libgmock.a` archive file in the test directory in order to compile the tests.

To create a `libgmock.a` file in a Linux system follow these instructions in an arbitrary directory.

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

Congratulations! You now have a `libgmock.a` archive file.

##Hermes google test setup

Create a `Epsilon-Hermes/build/.lib` directory using `mkdir -p Epsilon-Hermes/build/.lib` in the root directory and then place the `libgmock.a` archive file in the `Epsilon-Hermes/build/.lib/` directory and you should be good to go.
Run `qmake` and then `make check` in the `Epsilon-Hermes/src/` directory to run the tests.

Both gmock and the gtest folders located in `googletest/googlemock/include/` and `googletest/googletest/include/` need to be placed in the `/usr/local/include` system directory.

##TelemetryTestTool google test setup 

Create a `build/.lib` directory using `mkdir -p Location_of_your_local_Test Tool_repository/build/.lib` and then place the `libmock.a` archive file in the new `build/.lib/` directory and you should be good to go.
Use `ls -a` to show all hidden files.



