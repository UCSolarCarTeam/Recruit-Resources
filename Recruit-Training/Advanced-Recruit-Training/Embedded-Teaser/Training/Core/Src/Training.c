#include "Training.h"

void trainingTask(uint8_t* data)
{
	validData = 0;
	
	if (motorCheck(*data) && motorCheck(*data) == motorCheck(*(data + 1)) && lightsCheck(*(data + 2)) ) // set outputArray if motors data are valid, motors are in sync and lights data is valid
	{
		for (int i = 0; i < sizeof outputArray / sizeof *outputArray; i++)
		{
			outputArray[i] = *(data + i);
		}	
	}
	else
	{
		for (int i = 0; i < sizeof outputArray / sizeof *outputArray; i++)
		{
			outputArray[i] = 0;
		}	
	}
	
	if (motorCheck (*data))  // set first motor bit in validData to 1 if motor's data is valid
	{
		validData = validData | (1 << FIRSTMOTOR);
	}
	
	if (motorCheck (*(data + 1))) // set second motor bit in validData to 1 if motor's data is valid
	{
		validData = validData | (1 << SECONDMOTOR);
	}
	if (lightsCheck (*(data+2))) // set lights bit in validData to 1 if lights data is valid
	{
		validData = validData | (1 << LIGHTSBOARD);
	}	
}

int motorCheck (uint8_t testMotor)
{
	uint8_t motorMask = 0b11000001;
	
	if ((testMotor & motorMask) == 0b10000000) // check the case that motor is in reverse (power on, negative velocity and reverse)
		return 1;
	else if ((testMotor & motorMask) == motorMask) // check the case that motor is in forward (power on, positive velocity and forward)
		return 2;
	else if (testMotor == 0) // check case that power is off
		return 3;
	
	return 0;
}	

int lightsCheck (uint8_t testLight)
{
	uint8_t maskedHeadLights = testLight & 0b00000111;
	uint8_t maskedSignals = testLight & 0b00011000;
	
	if(!(maskedHeadLights && !(maskedHeadLights & (maskedHeadLights-1))) || !(maskedSignals && !(maskedSignals & (maskedSignals-1)))) // if more than 1 headlight state is chosen or more than one signal is on return 0
		return 0;
	
	return 1;
}
