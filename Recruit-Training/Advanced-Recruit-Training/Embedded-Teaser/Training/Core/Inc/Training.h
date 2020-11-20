#pragma once
#include <stdint.h>

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

typedef struct motorData_t {
  uint8_t direction : 1;
  int8_t velocity : 6;
  uint8_t on_off : 1;
} motorData_t;

void trainingTask(uint8_t* data); // data should be 3 elements wide (size of 3)
uint8_t checkMotors(uint8_t motor1, uint8_t motor2); // Determines if motor data is valid
uint8_t checkMotor(motorData_t motor); // Determines if one motor is valid
uint8_t checkLights(uint8_t lights); // Determines if lights data is valid.

motorData_t extractMotorData(uint8_t motorData);
