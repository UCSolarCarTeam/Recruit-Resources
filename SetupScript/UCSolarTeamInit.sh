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

git clone https://github.com/UCSolarCarTeam/Epsilon-Dashboard.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Raspberry.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Onboard-Media-Control.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Embedded-Software.git
git clone https://github.com/UCSolarCarTeam/Recruit-Resources.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Hermes.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Telemetry-Test-Tool.git
git clone https://github.com/UCSolarCarTeam/BackupCamera.git
git clone https://github.com/UCSolarCarTeam/Epsilon-Telemetry-Server.git

(cd ~/Documents/SolarCar/Epsilon-OnBoard-Media-Control/
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
sudo wget -q https://downloads.sourceforge.net/project/qwt/qwt/6.1.3/qwt-6.1.3.tar.bz2
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

sudo rm -r /tmp/solarcar/
