cd ~/Documents/SolarCar/Delta-Telemetry-Test-Tool/src
qmake 
make

cd ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/EmVer/
chmod +x emverTest.sh
./emverTest.sh
cd ~/Documents/SolarCar/Epsilon-Onboard-Media-Control/
make

cd ~/Documents/SolarCar/
sudo ./make-all

cd ~/Documents/SolarCar/DeltaHermes/Delta-Hermes/
qmake
make

cd ~/Documents/SolarCar/DeltaHermes/Delta-Hermes/Tests/
qmake
make

cd ~/Documents/SolarCar/EpsilonHermes/Epsilon-Hermes/
qmake
make

cd ~/Documents/SolarCar/EpsilonHermes/Epsilon-Hermes/Tests/
qmake 
make

cd ~/Documents/SolarCar/DeltaDesktopClientTelemetry/Delta-Desktop-Client-Telemetry/
qmake
make

cd ~/Documents/SolarCar/BackupCamera/
make

cd ~/Documents/Recruit-Resources/Advanced-Recruit-Training/src/
qmake
make

cd ~/Documents/SolarCar/DeltaTelemetryServer/Delta-Telemetry-Server/
go build
