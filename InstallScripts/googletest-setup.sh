#!/usr/bin/env bash
if [ "$(id -u)" != "0" ]; then
    echo "Permission Denied. Please run as root"
    exit 1
fi

# install googletest and googlemock
if ls /usr/local/include/gmock 1> /dev/null 2>&1 \
  && ls /usr/local/include/gtest 1> /dev/null 2>&1 \
  && ls /usr/local/lib/libgmock.a 1> /dev/null 2>&1;
then
  echo 'googletest & googlemock already installed'
else
(
  cd /tmp
  git clone https://github.com/google/googletest.git
  cp -r googletest/googletest/include/gtest /usr/local/include
  cp -r googletest/googlemock/include/gmock /usr/local/include
  (
    cd googletest
    g++ -std=c++11 \
        -isystem googletest/include/ \
        -Igoogletest \
        -isystem googlemock/include/ \
        -Igooglemock \
        -pthread \
        -c \
        googlemock/src/gmock-all.cc
    g++ -std=c++11 \
        -isystem googletest/include/ \
        -Igoogletest \
        -isystem googlemock/include/ \
        -Igooglemock \
        -pthread \
        -c \
        googletest/src/gtest-all.cc
    ar -rv libgmock.a gtest-all.o gmock-all.o
  )
  cp googletest/libgmock.a /usr/local/lib
)
fi