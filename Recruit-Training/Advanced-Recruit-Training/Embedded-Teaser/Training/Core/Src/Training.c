#include "Training.h"
/*
    CONDITIONS FOR FAILURE
    
    -the velocity and direction bit don't express the same direction
    -the input for the first and second motor aren't EXACTLY the same
    -more than one headlight choice is chosen
    -both left and right signals are on at the same time

*/
void trainingTask(uint8_t* data)
{
    uint8_t tempVelocityMotor1 = data[0] >> 6;
    tempVelocityMotor1 = tempVelocityMotor1 << 7;

    uint8_t tempVelocityMotor2 = data[0] >> 6;
    tempVelocityMotor2 = tempVelocityMotor2 << 7;

    if ((data[0] <<7 != tempVelocityMotor1)
         && (data[1] << 7 != tempVelocityMotor2))
    {
        if (data[0] == data[1])
        {
            outputArray[0] = data[0];
            outputArray[1] = data[1];
            validData |= 0b0000011;
        }
        else 
        {
           validData &= 0b11111100;  
        }
    }
    else 
    {
        validData &= 0b11111100;    
    }
    
    //Lights
    if (   (data[2]&0b00000111) == 0b100 
        || (data[2]&0b00000111) == 0b010
        || (data[2]&0b00000111) == 0b001)
        {
            if ( (data[2] & 0b00011000) != 0b00011000)
            {
                outputArray[2] = data[2];
                validData |= 0b00000100;
            }
            else
            {
                validData &= 0b11111011;
            }
            
        }

    else
    {
        validData &= 0b11111011;
    }
    
}
