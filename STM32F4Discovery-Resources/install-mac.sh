#!/usr/bin/env bash

# if [[ $UID != 0 ]]; then
#     echo "Please run this script with sudo:"
#     echo "sudo $0 $*"
#     exit 1
# fi

# brew install git autoconf pkg-config cmake
brew install git autoconf libusb pkg-config cmake


# Install STLink
if ! type "st-flash" > /dev/null; then
    echo "*** Installing ST Link"
    git clone https://github.com/UCSolarCarTeam/stlink.git /opt/stlink
    mkdir /opt/stlink/build
    (cd /opt/stlink/build && sudo cmake -DCMAKE_BUILD_TYPE=Debug .. && sudo make -j4)
    ln -s /opt/stlink/build/st-flash /usr/local/bin/st-flash
    ln -s /opt/stlink/build/st-info /usr/local/bin/st-info
    ln -s /opt/stlink/build/src/gdbserver/st-util /usr/local/bin/st-util
    sudo echo "export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:/opt/stlink/build" >> ~/.profile
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/stlink/build
    sudo echo "export PATH=\$PATH:/opt/stlink/build" >> ~/.profile
    export PATH=$PATH:/opt/stlink/build
else
    echo "*** ST Link already installed"
fi

# Install CubeMX2Makefile
if ! type "CubeMX2Makefile" > /dev/null; then
    echo "*** Installing CubeMX2Makefile"
    git clone https://github.com/UCSolarCarTeam/CubeMX2Makefile.git --depth 1
    mv CubeMX2Makefile /opt/CubeMX2Makefile
    echo "#!/usr/bin/env bash" >> /usr/local/bin/CubeMX2Makefile
    echo "ABS_PATH=\"\$(readlink -f \$1)\"" >> /usr/local/bin/CubeMX2Makefile
    echo "(cd /opt/CubeMX2Makefile && python CubeMX2Makefile.py \$ABS_PATH)" >> /usr/local/bin/CubeMX2Makefile
    chmod +x /usr/local/bin/CubeMX2Makefile
    echo "export PATH=\$PATH:/opt/CubeMX2Makefile" >> ~/.profile
    export PATH=$PATH:/opt/CubeMX2Makefile
else
    echo "*** CubeMX2Makefile already installed"
fi

# Install arm compiler
if [ ! -d "/opt/gcc4mbed" ]; then
    echo "*** Installing arm compiler"
    git clone https://github.com/UCSolarCarTeam/gcc4mbed.git /opt/gcc4mbed --depth 1
    (cd /opt/gcc4mbed && \
        sudo chmod +x mac_install && \
        sed -i '108d;109d;110d;147d' mac_install && \
        sudo ./mac_install)
    if ! grep "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" ~/.profile; then
        echo "export PATH=\$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile
    fi
    export PATH=$PATH:/opt/gcc4mbed/gcc-arm-none-eabi/bin/
	ln -s /opt/gcc4mbed/gcc-arm-none-eabi/bin/arm-none-eabi-gdb /usr/local/bin/arm-none-eabi-gdb
else
    echo "*** ARM compiler already installed"
fi

# Sourcing Profile
source ~/.profile
