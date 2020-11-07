#include "Training.h"

void trainingTask(uint8_t* data)
{
	uint8_t firstMotor = *data, secondMotor = *(data + 1), lightsInfo = *(data + 2);
	validData = 0;
	
	if (motorCheck(*data) && motorCheck(*data) == motorCheck(*(data + 1)) && lightsCheck(*(data + 2)) )
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
	
	if (motorCheck (*data)) 
	{
		validData = validData | (1 << FIRSTMOTOR);
	}
	
	if (motorCheck(*(data + 1)))
	{
		validData = validData | (1 << SECONDMOTOR);
	}
	
	if (lightsCheck(*(data + 2)))
	{
		validData = validData | (1 << LIGHTSBOARD);
	}
}

int motorCheck (uint8_t testMotor)
{
	uint8_t motorMask = 0xc1;
	
	if ((testMotor & motorMask) == 0x80)
		return 1;
	else if ((testMotor & motorMask) == motorMask)
		return 2;
	
	return 0;
}	

int lightsCheck (uint8_t testLight)
{
	uint8_t maskedHeadLights = testLight & 0x7;
	uint8_t maskedSignals = testLight & 0x18;
	
	if(!(maskedHeadLights && !(maskedHeadLights & (maskedHeadLights-1))) || !(maskedSignals && !(maskedSignals & (maskedSignals-1))))
		return 0;
	
	return 1;
}

