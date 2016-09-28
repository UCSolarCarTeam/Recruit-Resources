#!/usr/bin/env bash

if [[ $UID != 0 ]]; then
    echo "Please run this script with sudo:"
    echo "sudo $0 $*"
    exit 1
fi

apt-get -y install build-essential git libsane:i386 ia32-libs-multiarch autoconf libusb-1.0-0-dev pkg-config cmake

# Install arm compiler
if ! type "arm-none-eabi-gcc" > /dev/null; then
    echo "Installing arm compiler"
    git clone https://github.com/adamgreen/gcc4mbed /opt/gcc4mbed --depth 1
    (cd /opt/gcc4mbed && \
        chmod +x linux_install && \
        sed -i '108d;109d;110d;134d' linux_install && \
        ./linux_install)
    echo "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile
    export PATH=$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/
fi

# Install CubeMX
echo "Installing STM32CubeMX"
if [ ! -d "/opt/STM32CubeMX" ]; then
    mkdir cubemx
    cp auto-install.xml cubemx
    (cd cubemx && \
        wget https://s3-us-west-2.amazonaws.com/ucsolarteam.hostedfiles/en.stm32cubemx.zip && \
        unzip en.stm32cubemx.zip && \
        chmod +x SetupSTM32CubeMX-4.16.1.linux && \
        ./SetupSTM32CubeMX-4.16.1.linux auto-install.xml)
    rm -r cubemx
    ln -s ../../../opt/STM32CubeMX/STM32CubeMX /usr/local/bin/STM32CubeMX
fi

# Install STLink
if ! type "st-flash" > /dev/null; then
    echo "Installing ST Link"
    git clone https://github.com/texane/stlink.git /opt/stlink --depth 1
    mkdir /opt/stlink/build
    (cd /opt/stlink/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j4)
    echo "export PATH=\$PATH:/opt/stlink/build/" >> ~/.profile
    echo "export PATH=\$PATH:/opt/stlink/build/src/gdbserver" >> ~/.profile
    echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/stlink/build" >> ~/.profile
    export PATH=$PATH:/opt/stlink/build
    export PATH=$PATH:/opt/stlink/build/src/gdbserver
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/stlink/build
    rm -r stlink
fi

# Install CubeMX2Makefile
if ! type "CubeMX2Makefile" > /dev/null; then
    echo "Installing CubeMX2Makefile"
    git clone https://github.com/baoshi/CubeMX2Makefile.git --depth 1
    mv CubeMX2Makefile /opt/CubeMX2Makefile
    ln -s /opt/CubeMX2Makefile/CubeMX2Makefile.py /opt/CubeMX2Makefile/CubeMX2Makefile
    echo "export PATH=\$PATH:/opt/CubeMX2Makefile" >> ~/.profile
    export PATH=$PATH:/opt/CubeMX2Makefile
fi
