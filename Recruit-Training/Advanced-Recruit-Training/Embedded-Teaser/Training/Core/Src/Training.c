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
    
    if ((data[0] >> 7) != (data[1] >> 7)) // if the motors are not both ON or both OFF
    {
        invalidMotorInput();
    }
    
    else if (   ((data[0] >> 7) == 0)  // if  motor 1 is off AND the speed is not 0
             && (motor1Velocity != 0)
            )
    {
        invalidMotorInput();
    }

    else if (   ((data[1] >> 7) == 0)  // if  motor 2 is off AND the speed isn't 0
             && (motor2Velocity != 0)
            )
    {
        invalidMotorInput();   
    }
   
    else if (      (motor1Velocity != 0)                        //if motor1 velocity is not 0
                && (((data[0] >> 6) & 1) == motor1Direction)      //AND velocity sign bit and direction bit are the same 
            ) 
        {
            invalidMotorInput();
        }
    

    else if (      (motor2Velocity != 0)                        //if motor2 velocity is not 0
                && (((data[1] >> 6) & 1) == motor2Direction)      //AND velocity sign bit and direction bit are the same 
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
    
    if (   (data[2]&0b00000111) != 0b100 
        && (data[2]&0b00000111) != 0b010
        && (data[2]&0b00000111) != 0b001)  // if more than one headlight is active
        {
            invalidLightsInput();            
        }
    
    else if (     ((data[2] >> 5) & 1) == 1         //if    hazards lights are ON
                &&(leftSignal + rightSignal != 2)   //      AND the left and right signals are not Both ON
            )
        {
            invalidLightsInput();
        }

    else if (     ((data[2] >> 5) & 1) == 0         //if    hazards lights are OFF
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
