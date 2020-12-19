#pragma once
#include <stdint.h>

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

void trainingTask(uint8_t* data);  // data should be 3 elements wide (size of 3)

//ADDED FUNCTIONS
void invalidMotorInput();
void invalidLightsInput();

void validMotorInput(uint8_t* data);
void validLightsInput(uint8_t* data);

void checkMotors();
void checkLights();
