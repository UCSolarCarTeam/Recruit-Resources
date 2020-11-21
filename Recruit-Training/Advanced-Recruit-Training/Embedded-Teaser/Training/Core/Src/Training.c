#include "Training.h"
/*
    CONDITIONS FOR FAILURE
    
    -the velocity and direction bit don't express the same direction
    -If the motors are off, and the speeds dont have the same direction
    -Motors dont have the same direction
    -Motors aren't both on or both off
    -more than one headlight choice is chosen
    -both left and right signals are on at the same time when the hazards are off
    -hazards are on, but the signals are off

    **NOTE** - 2's compliment system is being used for velocity

*/
void trainingTask(uint8_t* data)
{
    //MOTORS

    uint8_t motor1Direction = data[0] & 1;
    uint8_t motor2Direction = data[1] & 1;

    uint8_t motor1Velocity = data[0] >> 1;
    motor1Velocity &= 0b00111111;

    uint8_t motor2Velocity = data[1] >> 1;
    motor2Velocity &= 0b00111111;

    uint8_t motor1VelocitySign = motor1Velocity >> 5;
    uint8_t motor2VelocitySign = motor2Velocity >> 5;

    uint8_t motor1IsOn = (data[0] >> 7);
    uint8_t motor2IsOn = (data[1] >> 7);
    
    if (motor1IsOn != motor2IsOn) // if the motors are not both ON or both OFF
    {
        invalidMotorInput();
    }
    
    else if (   (motor1IsOn == 0)  // if  motor 1 is off AND the speed is not 0
             && (motor1Velocity != 0)
            )
    {
        invalidMotorInput();
    }

    else if (   (motor2IsOn == 0)  // if  motor 2 is off AND the speed isn't 0
             && (motor2Velocity != 0)
            )
    {
        invalidMotorInput();   
    }
   
    else if (      (motor1Velocity != 0)                        //if motor1 velocity is not 0
                && (motor1VelocitySign == motor1Direction)      //AND velocity sign bit and direction bit are the same 
            ) 
        {
            invalidMotorInput();
        }
    

    else if (      (motor2Velocity != 0)                        //if motor2 velocity is not 0
                && (motor2VelocitySign == motor2Direction)      //AND velocity sign bit and direction bit are the same 
            ) 
        {
            invalidMotorInput();
        }
    
    
    else if (motor1Direction != motor2Direction)           //       if motor 1 and motor 2 have opposite direction 
    {
        invalidMotorInput();
    }

    else
    {
        validMotorInput(data);
    }
       
    //LIGHTS

    uint8_t rightSignal = (data[2] >> 3) & 1;
    uint8_t leftSignal = (data[2] >> 4) & 1;
    uint8_t hazardLight = (data[2] >> 5) & 1;
    uint8_t headlightsOff = data[2] & 1;
    uint8_t headlightsLow = (data[2] >> 1) & 1;
    uint8_t headlightsHigh = (data[2] >> 2) & 1; 
    
    if ( headlightsOff + headlightsLow + headlightsHigh != 1)  // if more than one headlight option is ON
        {
            invalidLightsInput();            
        }
    
    else if (     hazardLight         //if    hazards lights are ON
                &&(leftSignal + rightSignal != 2)   //      AND the left and right signals are not Both ON
            )
        {
            invalidLightsInput();
        }

    else if (     !hazardLight        //if    hazards lights are OFF
                &&(leftSignal + rightSignal == 2)   //      AND the left and right signals are Both ON
            )
        {
            invalidLightsInput();
        }
    
    else
    {
        validLightsInput(data);
    }
    
}

//ADDED FUNCTIONS

void invalidMotorInput()
{
    validData &= 0b11111100;
    return;
}

void invalidLightsInput()
{
    validData &= 0b11111011;
    return;
}

void validMotorInput(uint8_t* data)
{
    outputArray[0] = data[0];
    outputArray[1] = data[1];
    validData |= 0b0000011;

    return;
}

void validLightsInput(uint8_t* data)
{
    outputArray[2] = data[2];
    validData |= 0b00000100;

    return;
}
