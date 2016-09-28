#!/usr/bin/env bash

if [[ $UID != 0 ]]; then
    echo "Please run this script with sudo:"
    echo "sudo $0 $*"
    exit 1
fi

apt-get -y install build-essential git libsane:i386 ia32-libs-multiarch autoconf libusb-1.0-0-dev pkg-config cmake

# Install CubeMX
if [ ! -d "/opt/STM32CubeMX" ]; then
    echo "*** Installing STM32CubeMX"
    mkdir cubemx
    cp auto-install.xml cubemx
    (cd cubemx && \
        wget http://www.st.com/content/ccc/resource/technical/software/sw_development_suite/00/22/e1/cf/b7/83/42/25/stm32cubemx.zip/files/stm32cubemx.zip/jcr:content/translations/en.stm32cubemx.zip && \
        unzip en.stm32cubemx.zip && \
        chmod +x SetupSTM32CubeMX-*.linux && \
        ./SetupSTM32CubeMX-*.linux auto-install.xml)
    rm -r cubemx
else
    echo "*** STM32CubeMX already installed"
fi

# Install STLink
if ! type "st-flash" > /dev/null; then
    echo "*** Installing ST Link"
    git clone https://github.com/texane/stlink.git /opt/stlink --depth 1
    mkdir /opt/stlink/build
    (cd /opt/stlink/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j4)
    ln -s /opt/stlink/build/st-flash /usr/local/bin/st-flash
    ln -s /opt/stlink/build/st-info /usr/local/bin/st-info
    ln -s /opt/stlink/build/src/gdbserver/st-util /usr/local/bin/st-util
    echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/opt/stlink/build" >> ~/.profile
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/stlink/build
else
    echo "*** ST Link already installed"
fi

# Install CubeMX2Makefile
if ! type "CubeMX2Makefile" > /dev/null; then
    echo "*** Installing CubeMX2Makefile"
    git clone https://github.com/baoshi/CubeMX2Makefile.git --depth 1
    mv CubeMX2Makefile /opt/CubeMX2Makefile
    ln -s /opt/CubeMX2Makefile/CubeMX2Makefile.py /usr/local/bin/CubeMX2Makefile
else
    echo "*** CubeMX2Makefile already installed"
fi

# Install arm compiler
if [ ! -d "/opt/gcc4mbed" ]; then
    echo "*** Installing arm compiler"
    git clone https://github.com/adamgreen/gcc4mbed /opt/gcc4mbed --depth 1
    (cd /opt/gcc4mbed && \
        chmod +x linux_install && \
        sed -i '108d;109d;110d;134d' linux_install && \
        ./linux_install)
    if ! grep "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" ~/.profile; then
        echo "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile
    fi
    export PATH=$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/
else
    echo "*** ARM compiler already installed"
fi
