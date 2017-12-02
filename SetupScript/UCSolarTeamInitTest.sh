source ~/.profile

(cmake --version
git --version
subl --version
putty --version
nvim --version
qmake --version
go version)

echo "Testing Epsilon-Telemetry-Test-Tool"
(cd ~/Documents/SolarCar/Epsilon-Telemetry-Test-Tool
qmake 
make)

echo "Testing Epsilon-Dashboard"
(cd ~/Documents/SolarCar/Epsilon-Dashboard
qmake 
make)

echo "Testing Epsilon-Onboard-Media-Control"
(cd ~/Documents/SolarCar/Epsilon-Onboard-Media-Control/
make)

echo "Testing Recruit-Resources"
(cd ~/Documents/SolarCar/Recruit-Resources/Advanced-Training/src
qmake
make)

echo "Testing Epsilon-Hermes"
(cd ~/Documents/SolarCar/Epsilon-Hermes/
qmake
make)

(cd ~/Documents/SolarCar/Epsilon-Hermes/Tests/
qmake 
make)

echo "Testing BackupCamera"
(cd ~/Documents/SolarCar/BackupCamera/src
make)

echo "Testing Epsilon-Telemetry-Server"
(cd ~/Documents/SolarCar/Epsilon-Telemetry-Server/
go build)
