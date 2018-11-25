#!/usr/bin/env bash
if [ "$(id -u)" != "0" ]; then
    echo "Permission Denied. Please run as root"
    exit 1
fi
if [ -f /etc/os-release ]; then
   . /etc/os-release
   CODENAME=$VERSION_CODENAME
else
   CODENAME=$(lsb_release -sc)
fi

apt-key adv --keyserver "hkps.pool.sks-keyservers.net" --recv-keys "0x6B73A36E6026DFCA"
wget -O - "https://github.com/rabbitmq/signing-keys/releases/download/2.0/rabbitmq-release-signing-key.asc" | sudo apt-key add -

echo "deb https://dl.bintray.com/rabbitmq/debian $CODENAME main erlang" | sudo tee /etc/apt/sources.list.d/bintray.rabbitmq.list
(
	apt-get update
	apt-get install -y \
		erlang-nox \
		rabbitmq-server \
		cmake \
		libboost-dev \
		openssl \
		libssl-dev \
		libblkid-dev \
		e2fslibs-dev \
		libboost-all-dev \
		libaudit-dev \
		software-properties-common \
		build-essential \
		mesa-common-dev \
		libgl1-mesa-dev
)

(
	cd /tmp/
	if ls /usr/local/lib/librabbitmq.* 1> /dev/null 2>&1 ;
	then
		echo "Rabbitmq already installed"
	else
		if [ -d "rabbitmq-c" ] ; then
			echo "Cleaning tmp/rabbitmq-c"
			rm rabbitmq-c/ -r
		fi
		git clone https://github.com/alanxz/rabbitmq-c
		mkdir rabbitmq-c/build && cd rabbitmq-c/build
		cmake ..
		cmake --build .
		sudo cp librabbitmq/*.a /usr/local/lib/
		sudo cp librabbitmq/*.so* /usr/local/lib/
	fi
)

(
	cd /tmp/
	if ls /usr/local/lib/libSimpleAmqpClient.* 1> /dev/null 2>&1 && [ -d /usr/local/include/SimpleAmqpClient ];
	then
		echo "SimpleAmqpClient already installed"
	else
                if [ -d "SimpleAmqpClient" ] ; then
                        echo "Cleaning tmp/SimpleAmqpClient"
                        rm SimpleAmqpClient/ -r
                fi

		git clone https://github.com/alanxz/SimpleAmqpClient
		mkdir -p SimpleAmqpClient/build
		cd SimpleAmqpClient/build
		cmake -DRabbitmqc_INCLUDE_DIR=../../rabbitmq-c/librabbitmq -DRabbitmqc_LIBRARY=../../rabbitmq-c/build/librabbitmq ..
		make
		mkdir -p /usr/local/include/SimpleAmqpClient
		cp *.so* /usr/local/lib/
		cp ../src/SimpleAmqpClient/*.h /usr/local/include/SimpleAmqpClient
	fi
)
