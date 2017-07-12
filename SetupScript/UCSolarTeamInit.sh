#!/usr/bin/env bash
sudo mkdir -p /tmp/solarcar
sudo chmod +x qt-installer-noninteractive.qs
sudo chmod +x init.vim

sudo add-apt-repository -y ppa:neovim-ppa/unstable
sudo add-apt-repository -y ppa:webupd8team/sublime-text-3
sudo apt-get -qq update
sudo apt-get -q --yes  install cmake software-properties-common build-essential mesa-common-dev libgl1-mesa-dev git-all gitk sublime-text-installer neovim putty
sudo cp init.vim ~/.config/nvim/

sudo apt-get -q -o Dpkg::Options::="--force-condef" -o Dpkg::Options::="--force-confold" --yes --force-yes upgrade

echo "Installing Git Repositores in ~/Documents/SolarCar"
mkdir -p ~/Documents/SolarCar
(cd ~/Documents/SolarCar/
mkdir DeltaTelemetryServer
mkdir BackupCamera
mkdir DeltaHermes
mkdir EpsilonHermes
mkdir DeltaDesktopClientTelemetry

git clone https://github.com/UCSolarCarTeam/Epsilon-Domovoi.git
git clone https://github.com/UCSolarCarTeam/Recruit-Resources.git
git clone https://github.com/UCSolarCarTeam/Delta-Telemetry-Server.git DeltaTelemetryServer/Delta-Telemetry-Server
git clone https://github.com/UCSolarCarTeam/Delta-Telemetry-Test-Tool.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Embedded-Test-Tool.git
git clone https://github.com/UCSolarCarTeam/BackupCamera.git BackupCamera/Backup-Camera
git clone https://github.com/UCSolarCarTeam/Epsilon-Onboard-Media-Control.git
git clone https://github.com/UCSolarCarTeam/Delta-OnBoard-Media-Control.git
git clone https://github.com/UCSolarCarTeam/Delta-Hermes.git DeltaHermes/Delta-Hermes
git clone https://github.com/UCSolarCarTeam/Epsilon-Hermes.git EpsilonHermes/Epsilon-Hermes
git clone https://github.com/UCSolarCarTeam/Delta-Desktop-Client-Telemetry.git DeltaDesktopClientTelemetry/Delta-Desktop-Client-Telemetry)
(cd ~/Documents/SolarCar/Delta-OnBoard-Media-Control/
git clone https://github.com/google/googletest.git
(cp googletest ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/EmVer/ -r) #Send it to Epsilon-Embedded-Test-Tool
cd googletest
sudo cp -r googletest/include/gtest /usr/local/include
sudo cp -r googlemock/include/gmock /usr/local/include
g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googlemock/src/gmock-all.cc
g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googletest/src/gtest-all.cc
ar -rv libgmock.a gtest-all.o gmock-all.o
cp libgmock.a ../test/
(cp libgmock.a ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/EmVer/test/) #Send to Epsilion-Embedded-Test-Tool
(mkdir -p ~/Documents/SolarCar/DeltaHermes/build/.lib/
cp libgmock.a ~/Documents/SolarCar/DeltaHermes/build/.lib/) #Send to Delta-Hermes
sudo cmake -DBUILD_SHARED_LIBS=ON
sudo make
sudo cp -a include/gtest/ /usr/include/
sudo cp -a libgtest_main.so libgtest.so /usr/lib/)


(cd ~/Documents/SolarCar/Delta-OnBoard-Media-Control/
sudo chmod 755 make-all
sudo bash ./Installer/MainInstaller.sh
sudo bash ./Installer/AutoBootSetup.sh)

(cd ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/EmVer/googletest
sudo cp -r googletest/include/gtest /usr/local/include
sudo cp -r googlemock/include/gmock /usr/local/include
g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googlemock/src/gmock-all.cc
g++ -isystem googletest/include/ -Igoogletest -isystem googlemock/include/ -Igooglemock -pthread -c googletest/src/gtest-all.cc)

(cd /tmp/solarcar/

echo "Downloading QT Installer"
sudo wget -q http://download.qt.io/official_releases/online_installers/qt-unified-linux-x64-online.run
sudo chmod +x qt-unified-linux-x64-online.run)

echo "Installing QT into Home/Qt/"
/tmp/solarcar/qt-unified-linux-x64-online.run --script qt-installer-noninteractive.qs 

#Setting path to qmake
(sudo mkdir /etc/xdg/qtchooser
sudo cp default.conf /etc/xdg/qtchooser/)

(cd /tmp/solarcar/
echo "Installing QWT Plot in /usr/local"
sudo wget -q http://heanet.dl.sourceforge.net/project/qwt/qwt/6.1.3/qwt-6.1.3.tar.bz2
sudo tar -xvf  qwt-6.1.3.tar.bz2
sudo mv qwt-6.1.3/ /usr/local/
cd /usr/local/qwt-6.1.3/
$HOME/Qt/5.5/gcc_64/bin/qmake qwt.pro
sudo make
sudo make install)

(cd /tmp/solarcar/
echo "Installing golang in /usr/local"
sudo wget -q https://storage.googleapis.com/golang/go1.7.linux-amd64.tar.gz
sudo tar -xf go1.7.linux-amd64.tar.gz
sudo mv go/ /usr/local
echo 'export PATH=$PATH:/usr/local/go/bin' >> ~/.profile )

(cd /usr/local
echo "Installing arm compiler in /usr/local"
sudo git clone https://github.com/adamgreen/gcc4mbed.git
cd /usr/local/gcc4mbed/
sudo sed -i '108d;109d;110d;134d' linux_install # Remove 'press any key to continue' and building samples
sudo ./linux_install
echo "export PATH=\$PATH:/usr/local/gcc4mbed/gcc-arm-none-eabi/bin/" >> ~/.profile)

sudo rm -r /tmp/solarcar/
