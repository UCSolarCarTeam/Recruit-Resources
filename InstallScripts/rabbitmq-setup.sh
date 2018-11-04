#!/usr/bin/env bash
if [ "$(id -u)" != "0" ]; then
    echo "Permission Denied. Please run as root"
    exit 1
fi

echo 'deb http://www.rabbitmq.com/debian/ testing main' | tee /etc/apt/sources.list.d/rabbitmq.list

(
	apt-get update
	apt-get install -y --force-yes rabbitmq-server \
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
