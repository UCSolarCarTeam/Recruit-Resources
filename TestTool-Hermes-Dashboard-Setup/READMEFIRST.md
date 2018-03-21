# READMEFIRST.md

In order test communications between Hermes, the telemetry test tool and the dashboard, two additional repositories need to be cloned and configured. The repositories are: RabbitMQ and SimpleAmqpClient. Individual setups are required for each program.

## RabbitMQ Broker

1) Installing rabbitMQ

In order to send messages, you must have a rabbitMQ server to send the messages to.
This can be installed [here](https://www.rabbitmq.com/) or via the package manager using:

`echo 'deb http://www.rabbitmq.com/debian/ testing main' | sudo tee /etc/apt/sources.list.d/rabbitmq.list && sudo apt-get update && sudo apt-get install rabbitmq-server`

## SimpleAmqpClient

1) Installing dependencies for SimpleAmqpClient

First, boost and cmake is required to generate the libraries below, you may install these using your appropriate package manager (such as apt-get on debian).
The following are the commands that could be used on a debian based distro to install these dependencies if you do not already have them.

`sudo apt-get install cmake libboost-dev openssl libssl-dev libblkid-dev e2fslibs-dev libboost-all-dev libaudit-dev`

SimpleAmqpClient requires rabbitmq-c, which can be downloaded and compiled from the repository [alanxz/rabbitmq-c](https://github.com/alanxz/rabbitmq-c).
Start by cloning the repository from github, this is recommended to be done in the `/tmp/` directory:

`git clone https://github.com/alanxz/rabbitmq-c`

Create a build directory and enter it with the following command:

`mkdir rabbitmq-c/build && cd rabbitmq-c/build`

You can now use cmake to generate the library required by SimpleAmqpClient:

`cmake ..`

`cmake --build .`

There should now be a `.a` file in your current directory, as well as multiple `*.so*` files. Use the following commands to make them visible to SimpleAmqpClient:

`sudo cp librabbitmq/*.a /usr/local/lib/`

`sudo cp librabbitmq/*.so* /usr/local/lib/`

3) Generating SimpleAmqpClient library

SimpleAmqpClient can be downloaded and compiled from [alanxz/SimpleAmqpClient](https://github.com/alanxz/SimpleAmqpClient).
Run the following command, recommended in the `/tmp/` directory:

`git clone https://github.com/alanxz/SimpleAmqpClient`

And once again generate a build directory and navigate to it:

`mkdir SimpleAmqpClient/build && cd SimpleAmqpClient/build`

Run the following commands to generate the libraries needed by Hermes:

`cmake -DRabbitmqc_INCLUDE_DIR=../../rabbitmq-c/librabbitmq -DRabbitmqc_LIBRARY=../../rabbitmq-c/build/librabbitmq ..`

`make`

4) Including the generated SimpleAmqpClient library

The generated library needs to be included in the list of local libraries. To do this, first generate a directory for it:

`sudo mkdir /usr/local/include/SimpleAmqpClient`

Then, run the following commands to copy the library over:

`sudo cp *.so* /usr/local/lib/`

`sudo cp ../src/SimpleAmqpClient/*.h /usr/local/include/SimpleAmqpClient`

5) Configure linker

After adding the library files to `/usr/local/lib`, configure the dynamic linker with SimpleAmqpClient with:

`sudo ldconfig`

### Start Server

`sudo rabbitmq-server` can be used to start the server on Linux.

### Refresh Server

On linux to refresh the contents of the server perform the following commands:

`rabbitmqctl stop_app`

`rabbitmqctl reset`

`rabbitmqctl start_app`
