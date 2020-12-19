#include "Training.h"
#include <math.h>

uint8_t selectBit(uint8_t bits, int index){
	return (bits >> index) & 0x01; //Only requesting one bit, so return bit at index
}

uint8_t selectBits(uint8_t bits, int index, int end){
	if(end < index)
		return -1; //End must be greater than index
	uint8_t returnVal = bits >> index;
	uint8_t range = end - index + (index == 0 ? 1 : 0); // calculate number of bits requested
	uint8_t maskBits = 0;
	for(int i = 0; i < range; i++)
		maskBits += pow(2, i);		// Determine mask bits
	return returnVal & maskBits;
}

void testMotors(uint8_t* data){
	uint8_t motor1Data = data[0];
	uint8_t motor2Data = data[1];
	int motor1On = selectBit(motor1Data, 7);			// Motor 1 on
	int motor2On = selectBit(motor2Data, 7);			// Motor 2 on
	int speed1 = selectBits(motor1Data, 1, 5); 			// Speed of motor 1
	int speed2 = selectBits(motor2Data, 1, 5); 			// Speed of motor 2
	int forward1 = selectBit(motor1Data, 0);			// Select bit 0 of motor 1
	int forward2 = selectBit(motor2Data, 0);			// Select bit 0 of motor 2
	int sign1 = selectBit(motor1Data, 6);				// Direction of velocity of motor1
	int sign2 = selectBit(motor2Data, 6);				// Direction of velocity of motor2
	if((motor1On == motor2On) &&
		(motor2On == 0)){								// If both motors off
		if((speed1 == speed2) &&
			(speed2 == 0))								// and speed is 0 it's valid
			validData += 3;
	} else if(motor1On == motor2On){					// If both motors on
		if(forward1 == forward2) {						// If motors going in the same direction
			if(forward1 == !sign1)						// If motor1 is going in same direction as velocity
				validData += 1;							// it's valid

			if(forward2 == !sign2) 	// If motor2 is going in same direction as velocity
				validData += 2;							// it's valid
		}
	}
	if(validData != 0b11)	//If either motor is invalid
		validData = 0;		//Set both to be invalid
}

void testLights(uint8_t* data){
	uint8_t lightData = data[2];
	int headlights = selectBits(lightData, 0, 2);					// Select bits that represent headlights
	if(	headlights == 0b001 || 
		headlights == 0b010 ||
		headlights == 0b100) {		// If headlights are in more than one state it's invalid
		if((lightData >> 5) & 1) {			// If hazards are on
			if((lightData >> 3) & 1 && 		// and both signals are on
				(lightData >> 4) & 1)
				validData += 4;				// it's valid
		} else if(((lightData >> 3) & 1) + 	// If hazards are off and only one or neither signal is on
			((lightData >> 4) & 1) <= 1)
			validData += 4;					// it's valid
	}
}

void trainingTask(uint8_t* data)
{	
	validData = 0;
	testMotors(data);	//Testing motors
	testLights(data);	//Testing lights
	//Updating output array
	outputArray[0] = selectBit(validData, 0);
	outputArray[1] = selectBit(validData, 1);
	outputArray[2] = selectBit(validData, 2);
}
