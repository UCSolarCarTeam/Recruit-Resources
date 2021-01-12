#pragma once
#include <stdint.h>
#include <stdbool.h>

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

uint8_t m1Direction;
uint8_t m2Direction;

uint8_t m1Velocity;
uint8_t m2Velocity;

uint8_t m1VelocitySign;
uint8_t m2VelocitySign;

uint8_t m1Power;
uint8_t m2Power;

uint8_t headlightsOff;
uint8_t headlightsLow;
uint8_t headlightsHigh;

uint8_t rightSignal;
uint8_t leftSignal;

uint8_t hazards;
uint8_t brakes;

void trainingTask(uint8_t* data); // data should be 3 elements wide (size of 3)
void loadMotorData(uint8_t m1, uint8_t m2);
void loadLightData(uint8_t lights);
bool checkMotors();
bool checkLights();