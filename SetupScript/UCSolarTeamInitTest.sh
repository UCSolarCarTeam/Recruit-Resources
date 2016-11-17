source ~/.profile

(cmake --version
git --version
subl --version
putty --version
nvim --version
qmake --version
go version)

echo "Testing Delta-Telemetry-Test-Tool"
(cd ~/Documents/SolarCar/Delta-Telemetry-Test-Tool/src
qmake 
make)

echo "Testing Epsilon-Embedded-Test-Tool"
(cd ~/Documents/SolarCar/Epsilon-Embedded-Test-Tool/EmVer/
chmod +x emverTest.sh
./emverTest.sh)

echo "Testing Epsilon-Onboard-Media-Control"
(cd ~/Documents/SolarCar/Epsilon-Onboard-Media-Control/
make)

(cd ~/Documents/SolarCar/
sudo ./make-all)

echo "Testing Delta-Hermes"
(cd ~/Documents/SolarCar/DeltaHermes/Delta-Hermes/
qmake
make)

(cd ~/Documents/SolarCar/DeltaHermes/Delta-Hermes/Tests/
qmake
make)

echo "Testing Epsilon-Hermes"
(cd ~/Documents/SolarCar/EpsilonHermes/Epsilon-Hermes/
qmake
make)

(cd ~/Documents/SolarCar/EpsilonHermes/Epsilon-Hermes/Tests/
qmake 
make)

echo "Testing Delta-Desktop-Client-Telemetry"
(cd ~/Documents/SolarCar/DeltaDesktopClientTelemetry/Delta-Desktop-Client-Telemetry/
qmake
make)

echo "Testing BackupCamera"
(cd ~/Documents/SolarCar/BackupCamera/Backup-Camera/
make)

echo "Testing Delta-Telemetry-Server"
(cd ~/Documents/SolarCar/DeltaTelemetryServer/Delta-Telemetry-Server/
go build)
