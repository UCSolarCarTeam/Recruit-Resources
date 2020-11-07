#include "Training.h"

void trainingTask(uint8_t* data)
{	
	validData = 0;
	uint8_t motor1Data = data[0];
	uint8_t motor2Data = data[1];
	int forward1 = motor1Data >> 7;						// Select bit 7 of motor 1
	int forward2 = motor2Data >> 7;						// Select bit 7 of motor 2
	int speed1 = (motor1Data & 0b00111110) >> 1; 		// Speed of motor 1
	int speed2 = (motor2Data & 0b00111110) >> 1; 		// Speed of motor 2
	int motor1On = motor1Data & 1;						// Motor 1 on
	int motor2On = motor2Data & 1;						// Motor 2 on
	int sign1 = (motor1Data >> 6) & 1;					// Direction of velocity of motor1
	int sign2 = (motor2Data >> 6) & 1;					// Direction of velocity of motor2
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

	uint8_t lightData = data[2];
	int headlights = lightData & 0x07;								// Select bits that represent headlights
	if(headlights == 1 || headlights == 2 || headlights == 4) {		// If headlights are in more than one state it's invalid
		if((lightData >> 5) & 1) {			// If hazards are on
			if((lightData >> 3) & 1 && 		// and both signals are on
				(lightData >> 4) & 1)
				validData += 4;				// it's valid
		} else if(((lightData >> 3) & 1) + 	// If hazards are off and only one or neither signal is on
			((lightData >> 4) & 1) <= 1)
			validData += 4;					// it's valid
	}
}