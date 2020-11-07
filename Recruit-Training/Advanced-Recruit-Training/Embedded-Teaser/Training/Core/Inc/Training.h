#pragma once
#include <stdint.h>

uint8_t outputArray[3];
uint8_t validData; // Set bits 0, 1, 2 if the input array elements were valid

void trainingTask(uint8_t* data); // data should be 3 elements wide (size of 3)

int motorCheck (uint8_t testMotor); //function to test validity of motor data

int lightsCheck (uint8_t testLight); // function to test validity of lights board data

enum {FIRSTMOTOR, SECONDMOTOR, LIGHTSBOARD}; // enumerate indexes used in validData for ease of use
