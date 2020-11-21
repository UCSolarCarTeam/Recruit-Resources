#include "Training.h"
#include <stdio.h>

void trainingTask(uint8_t* data)
{
    uint8_t validity = 0b00000111;

    checkmotors(&validity, data[0], data[1]);

    checklights(&validity, data[2]);


    if( getbit(validity, 0) && getbit(validity, 1)) {
        outputArray[0] = data[0];
        outputArray[1] = data[1];
    }
    if (getbit(validity, 2)){
        outputArray[2] = data[2];
    }

    validData = validity;

}

uint8_t getbit(uint8_t data,int number)
{
    return (data & 1<<number);
}

int getvelocity(uint8_t data)
{
    int velocity  = getbit(data, 1) + getbit(data, 2) + getbit(data, 3) + getbit(data, 4) + getbit(data, 5);

    if (getbit(data, 6))
    velocity *=-1;

    return velocity;
}

void checkmotors(uint8_t *validity, uint8_t motor1, uint8_t motor2)
{
    int velocity1 = getvelocity(motor1);
    int velocity2 = getvelocity(motor2);

    int Motor1State = getbit(motor1, 7);
    if (Motor1State != getbit(motor2, 7)){  //check both motors are either turned on or off
        *validity &= ~0b00000011;
        return;
    } 

    if(Motor1State == 0){ //if motors are off, check velocity is 0

        if (velocity1 != 0)
        *validity &= ~0b00000011;
        if (velocity2 != 0)
        *validity &= ~0b00000011;

    } else { //if motors are on, check velocities and directions make sense

        if (velocity1*velocity2 < 0)  //check velocities are going the same direction
        *validity &= ~0b00000011;

        int VelocityDirection1 = velocity1 > 0;
        if (getbit(motor1, 0) != VelocityDirection1) // check motor 1 direction matches its velocity
        *validity &= ~0b00000001;

        int VelocityDirection2 = velocity2 > 0;
        if (getbit(motor2, 0) != VelocityDirection2) // check motor 2 direction matches its velocity
        *validity &= ~0b00000010;
    }

}

void checklights(uint8_t *validity, uint8_t lights)
{

    if (!getbit(lights, 5)) {                        
         if (getbit(lights, 3) && getbit(lights, 4))     //if hazards lights are not on, check that not both turn signals are on
        *validity &= ~0b00000100;
    }                       

    int Lowlights = getbit(lights, 1);
    int Highlights = getbit(lights, 2);

    if (getbit(lights, 0)) {                        //if headlights are off, check all modes are off
        if (Lowlights|| Highlights)
        *validity &= ~0b00000100;
    } else {                                        // if headlights are on, check that exactly one mode is on
        if (!Lowlights && !Highlights)
        *validity &= ~0b00000100;
        if (Lowlights && Highlights)               
        *validity &= ~0b00000100;
    }
}
