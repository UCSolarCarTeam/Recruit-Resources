#include "Training.h"

void trainingTask (uint8_t* data)
{
	validData = 0;
	int motorOneState = motorCheck (*data);
	int motorTwoState = motorCheck (*(data + 1));
	int lightState = lightsCheck (*(data + 2));
	
	if (motorOneState && motorOneState == motorTwoState) // set outputArray values of motor if motors data are valid, motors are in sync
	{
		outputArray[0] = *data;
		outputArray[1] = *(data + 1);
	}
	else
	{
		outputArray[0] = 0;
		outputArray[1] = 0;
	}
	
	if (lightState) // set outputArray values of lights if lights data are valid
	{
		outputArray[2] = *(data + 2);
	}
	else
	{
		outputArray[2] = 0;
	}	
	
	if (motorOneState)  // set first motor bit in validData to 1 if motor's data is valid
	{
		validData = validData | (1 << FIRSTMOTOR);
	}
	
	if (motorTwoState) // set second motor bit in validData to 1 if motor's data is valid
	{
		validData = validData | (1 << SECONDMOTOR);
	}
	
	if (lightState) // set lights bit in validData to 1 if lights data is valid
	{
		validData = validData | (1 << LIGHTSBOARD);
	}	
}

int motorCheck (uint8_t testMotor)
{
	uint8_t forwardMask = 0b10000001;
	uint8_t reverseMask = 0b11000000;
	
	if ((testMotor & forwardMask) == forwardMask) // check the case that motor is in reverse (power on, negative velocity and reverse)
		return 1;
	else if ((testMotor & reverseMask) == reverseMask) // check the case that motor is in forward (power on, positive velocity and forward)
		return 2;
	else if ((testMotor & 0b00000001) == 0b00000001) // check case that power is off and motor on "forward"
		return 3;
	else if (testMotor == 0) // check case that power is off
		return 4;	
	
	return 0;
}	

int lightsCheck (uint8_t testLight)
{
	uint8_t maskedHeadLights = testLight & 0b00000111;
	uint8_t maskedSignals = testLight & 0b00011000;
	uint8_t maskedHazards = testLight & 0b00111000;
	uint8_t hazardsOn = testLight & 0b00100000;
	int oneHeadlightOn = maskedHeadLights && !(maskedHeadLights & (maskedHeadLights-1));
	int oneSignalOn = maskedSignals && !(maskedSignals & (maskedSignals-1));
	
	if(!oneHeadlightOn || (hazardsOn && maskedHazards != 0b00111000) || (!hazardsOn && !oneSignalOn)) // if more than 1 headlight state is chosen or both signals are not on while hazard is on or more than one signal is on return 0
		return 0;
	
	return 1;
}
