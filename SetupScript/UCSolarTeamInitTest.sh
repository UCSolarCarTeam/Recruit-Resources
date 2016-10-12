cd ~/Documents/SolarCar/DeltaTelemetryTestTool/Delta-Telemetry-Test-Tool/
qmake
make
cd ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/
chmod +x emverTest.sh
./emverTest.sh
cd ~/Documents/SolarCar/Epsilon-Onboard-Media-Control/
make
cd ~/Documents/SolarCar/Delta-Onboard-Media-Control/
sudo chmod 755 make-all
sudo bash ./Installer/MainInstaller.sh
sudo bash ./Installer/AutoBootSetup.sh

cd ..
sudo ./make-all
cd ~/Documents/SolarCar/DeltaHermes/Delta-Hermes/
qmake
make
cd ~/Documents/SolarCar/EpsilonHermes/Epsilon-Hermes/
qmake
make
cd ~/Documents/SolarCar/AndroidClientTelemetry/Android-Client-Telemetry/
qmake
make
cd ~/Documents/SolarCar/DeltaDesktopClientTelemetry/Delta-Desktop-Client-Telemetry/
qmake
make
cd ~/Documents/SolarCar/BackupCamera/
make
cd ~/Documents/Recruit-Training/src/
qmake
make
cd ~/Documents/SolarCar/DeltaTelemetryServer/Delta-Telemetry-Server/
go build

