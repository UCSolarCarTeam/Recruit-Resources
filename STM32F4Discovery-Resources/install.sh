#!/usr/bin/env bash

USER=`whoami`
if [ $USER = "root" ]
    then
    echo "Running as ROOT"
else
    echo "***********YOU ARE NOT ROOT************"
    exit 0
fi

apt-get -y install build-essential git libsane:i386 ia32-libs-multiarch autoconf libusb-1.0-0-dev pkg-config cmake

# Install arm compiler
if ! type "arm-none-eabi-gcc" > /dev/null; then
    git clone https://github.com/adamgreen/gcc4mbed /opt/gcc4mbed --depth 1
    (cd /opt/gcc4mbed && \
        chmod +x linux_install && \
        sed -i '108d;109d;110d;134d' linux_install && \
        ./linux_install)
    export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/
    echo "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile
fi

# Install CubeMX
mkdir cubemx
cp auto-install.xml cubemx
(cd cubemx && \
    wget https://s3-us-west-2.amazonaws.com/ucsolarteam.hostedfiles/en.stm32cubemx.zip && \
    unzip en.stm32cubemx.zip && \
    chmod +x SetupSTM32CubeMX-4.16.1.linux && \
    ./SetupSTM32CubeMX-4.16.1.linux auto-install.xml)
rm -r cubemx

# Install STLink
if ! type "st-flash" > /dev/null; then
    git clone https://github.com/texane/stlink.git --depth 1
    mkdir stlink/build
    (cd stlink/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j4)
    mkdir /opt/stlink
    mv stlink/build /opt/stlink/build
    echo "export PATH=\$PATH:/opt/stlink/build/" >> ~/.profile
    echo "export PATH=\$PATH:/opt/stlink/build/src/gdbserver" >> ~/.profile
    export PATH=\$PATH:/opt/stlink/build
    export PATH=\$PATH:/opt/stlink/build/src/gdbserver
    rm stlink -rf
fi

# Install CubeMX2Makefile
if ! type "CubeMX2Makefile" > /dev/null; then
    git clone https://github.com/baoshi/CubeMX2Makefile.git /opt/CubeMX2Makefile --depth 1
    ln -s /opt/CubeMX2Makefile/CubeMX2Makefile.py /opt/CubeMX2Makefile/CubeMX2Makefile
    echo "export PATH=\$PATH:/opt/CubeMX2Makefile" >> ~/.profile
    export PATH=\$PATH:/opt/CubeMX2Makefile
fi
