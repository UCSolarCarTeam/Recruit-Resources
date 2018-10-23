#!/usr/bin/env bash
if [ "$(id -u)" != "0" ]; then
    echo "Permission Denied. Please run as root"
    exit 1
fi

echo 'deb http://www.rabbitmq.com/debian/ testing main' | tee /etc/apt/sources.list.d/rabbitmq.list

(
	apt-get update
	apt-get install rabbitmq-server \
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