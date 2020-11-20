#include "Training.h"

uint8_t checkHeadlights(uint8_t headlightsOn, uint8_t headlightsLow, uint8_t headlightsHigh);
uint8_t checkHazard(uint8_t hazards, uint8_t rightSignal, uint8_t leftSignal, uint8_t brakes);

void trainingTask(uint8_t* data)
{
    uint8_t motor1 = data[0];
    uint8_t motor2 = data[1];
    
    uint8_t motor1Forward = motor1 & 0x1;
    uint8_t motor2Forward = motor2 & 0x1;

    uint8_t motor1VelocityPositive = ~(motor1 >> 6) & 0x1;
    uint8_t motor1Velocity = motor1 & (0x3f << 1); 

    uint8_t motor2VelocityPositive = ~(motor2 >> 6) & 0x1;
    uint8_t motor2Velocity = motor2 & (0x3f << 1);

    uint8_t motor1On = motor1 >> 7;
    uint8_t motor2On = motor2 >> 7;

    if (motor1On && motor2On)
    {
        //both forward and velocity is positive
        if (motor1Forward && motor1VelocityPositive && motor2Forward && motor2VelocityPositive)
        {
            //write to output array
            outputArray[0] = motor1;
            outputArray[1] = motor2;

            validData &= ~0x2; //clear first two bits
            validData |= 0x2; //set first two bits
        }

        //both reverse and negative velocity
        if (!motor1Forward && !motor1VelocityPositive && !motor2Forward && !motor2VelocityPositive)
        {
            //write to output array
            outputArray[0] = motor1;
            outputArray[1] = motor2;

            validData &= ~0x2; //clear first two bits
            validData |= 0x2; //set first two bits
        }
        
    }else
    {   
        //motor 1 and 2 off and velocity 0
        if(!motor1On && motor1Velocity == 0x0 && !motor2On && motor2Velocity == 0x0)
        {
            //write to output array
            outputArray[0] = motor1;
            outputArray[1] = motor2;
            validData |= 0x2; 
        }

    }

    uint8_t lights = data[2];

    uint8_t headlightsOn = lights & 0x1;
    uint8_t headlightsLow = (lights >> 1) & 0x1;
    uint8_t headlightsHigh = (lights >> 2) & 0x1; 
    uint8_t rightSignal = (lights >> 3) & 0x1;
    uint8_t leftSignal = (lights >> 4) & 0x1;
    uint8_t hazards = (lights >> 5) & 0x1;
    uint8_t brakes = (lights >> 6) & 0x1;

    if (checkHeadlights(headlightsOn, headlightsLow, headlightsHigh) && checkHazard(hazards, rightSignal, leftSignal, brakes))
    {
            outputArray[2] &= ~0xff; //clear bits 0-6
            outputArray[2] |= headlightsOn; //set bit 0
            outputArray[2] |= headlightsLow << 1; //set bit 1
            outputArray[2] |= headlightsHigh << 2; //set bit 2
            outputArray[2] |= rightSignal << 3; //set bit 3
            outputArray[2] |= leftSignal << 4; //set bit 4
            outputArray[2] |= hazards << 5; //set bit 5
            outputArray[2] |= brakes << 6; //set bit 6
            
            validData &= ~(0x1 << 2); //clear bit 2
            validData |= 0x1; //set bit 2
    }
}

uint8_t checkHeadlights(uint8_t headlightsOn, uint8_t headlightsLow, uint8_t headlightsHigh)
{
    if (headlightsOn)
    {
        //if headlights on it means either it's high or low 
        if(headlightsLow && !headlightsHigh || headlightsHigh && !headlightsLow)
        {
           return 1;
        }
    }
    else
    {
        if(!headlightsHigh && !headlightsLow)
        {
            return 1;
        }
    }

    return 0;
}

uint8_t checkHazard(uint8_t hazards, uint8_t rightSignal, uint8_t leftSignal, uint8_t brakes)
{
    if(hazards)
    {
        if (rightSignal && leftSignal && brakes)
        {
            return 1;
        }
    }
    else
    {
        //either right or left signal is on or both off Brakes can be on or off. 
        if(rightSignal && !leftSignal || leftSignal && !rightSignal || !(rightSignal && leftSignal)){
            return 1;
        }
    }

    return 0;
}
