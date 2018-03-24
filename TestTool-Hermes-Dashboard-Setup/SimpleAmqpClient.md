#SimpleAmqpClient.md 

##SimpleAmqpClient

1) Generating SimpleAmqpClient library

SimpleAmqpClient can be downloaded and compiled from [alanxz/SimpleAmqpClient](https://github.com/alanxz/SimpleAmqpClient).
Run the following command, recommended in the `/tmp/` directory:

`git clone https://github.com/alanxz/SimpleAmqpClient`

And once again generate a build directory and navigate to it:

`mkdir SimpleAmqpClient/build && cd SimpleAmqpClient/build`

Run the following commands to generate the libraries needed by Hermes:

`cmake -DRabbitmqc_INCLUDE_DIR=../../rabbitmq-c/librabbitmq -DRabbitmqc_LIBRARY=../../rabbitmq-c/build/librabbitmq ..`

`make`

2) Including the generated SimpleAmqpClient library

The generated library needs to be included in the list of local libraries. To do this, first generate a directory for it:

`sudo mkdir /usr/local/include/SimpleAmqpClient`

Then, run the following commands to copy the library over:

`sudo cp *.so* /usr/local/lib/`

`sudo cp ../src/SimpleAmqpClient/*.h /usr/local/include/SimpleAmqpClient`

3) Configure linker

After adding the library files to `/usr/local/lib`, configure the dynamic linker with SimpleAmqpClient with:

`sudo ldconfig`
