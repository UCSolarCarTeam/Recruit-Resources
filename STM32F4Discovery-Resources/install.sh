#!/usr/bin/env bash

sudo apt-get -y install build-essential git libsane:i386 ia32-libs-multiarch autoconf libusb-1.0-0-dev pkg-config cmake

# Install arm compiler
if ! type "arm-none-eabi-gcc" > /dev/null; then
    git clone https://github.com/adamgreen/gcc4mbed /opt/gcc4mbed
    (cd /opt/gcc4mbed && \
        chmod +x linux_install && \
        sed -i '108d;109d;110d;134d' linux_install && \ # Remove 'press any key to continue' and building samples
        ./linux_install)
   echo "export PATH=$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile
fi

# Install CubeMX
mkdir cubemx
cp auto-install.xml cubemx
(cd cubemx && \
    wget https://s3-us-west-2.amazonaws.com/ucsolarteam.hostedfiles/en.stm32cubemx.zip && \
    unzip en.stm32cubemx.zip && \
    chmod +x SetupSTM32CubeMX-4.16.1.linux && \
    sudo ./SetupSTM32CubeMX-4.16.1.linux auto-install.xml)
rm -r cubemx

# Install STLink
git clone https://github.com/texane/stlink.git --depth 1
mkdir stlink/build
(cd stlink/build && cmake -DCMAKE_BUILD_TYPE=Debug .. && make -j4)
sudo cp stlink/build/st-flash /usr/local/bin/st-flash
sudo cp stlink/build/st-info /usr/local/bin/st-info
sudo cp stlink/build/src/gdbserver/st-util /usr/local/bin/st-util
rm stlink -rf

# Install CubeMX2Makefile
sudo git clone https://github.com/baoshi/CubeMX2Makefile.git /opt/CubeMX2Makefile
sudo ln -s /opt/CubeMX2Makefile/CubeMX2Makefile.py /opt/CubeMX2Makefile/CubeMX2Makefile
echo "export PATH=\$PATH:/opt/CubeMX2Makefile" >> ~/.profile

# source PATH changes
source  ~/.profile
