#include "Training.h"
#include <stdio.h>

void trainingTask(uint8_t* data)
{
    uint8_t validity = 0b00000111;

    checkMotors(&validity, data[0], data[1]);

    checkLights(&validity, data[2]);


    if (getBit(validity, 0) && getBit(validity, 1)) {
        outputArray[0] = data[0];
        outputArray[1] = data[1];
    }
    if (getBit(validity, 2)){
        outputArray[2] = data[2];
    }

    validData = validity;

}

uint8_t getBit(uint8_t data,int number)
{
    return (data & 1<<number);
}

int getVelocity(uint8_t data)
{
    int velocityBits  = getBit(data, 1) + getBit(data, 2) + getBit(data, 3) + getBit(data, 4) + getBit(data, 5);
    int velocity = velocityBits >> 1;

    if (getBit(data, 6))
    velocity *=-1;

    return velocity;
}

void checkMotors(uint8_t *validity, uint8_t motor1, uint8_t motor2)
{
    int velocity1 = getVelocity(motor1);
    int velocity2 = getVelocity(motor2);

    int motor1State = getBit(motor1, 7);
    if (motor1State != getBit(motor2, 7)) {  //check both motors are either turned on or off
        *validity &= ~0b00000011;
        return;
    } 

    if (motor1State == 0) { //if motors are off, check velocity is 0

        if (velocity1 != 0)
        *validity &= ~0b00000011;
        if (velocity2 != 0)
        *validity &= ~0b00000011;

    } else { //if motors are on, check velocities and directions make sense

        if (velocity1*velocity2 < 0)  //check velocities are going the same direction
        *validity &= ~0b00000011;

        int velocityDirection1 = velocity1 > 0;
        if (getBit(motor1, 0) != velocityDirection1) // check motor 1 direction matches its velocity
        *validity &= ~0b00000011;

        int velocityDirection2 = velocity2 > 0;
        if (getBit(motor2, 0) != velocityDirection2) // check motor 2 direction matches its velocity
        *validity &= ~0b00000011;
    }

}

void checkLights(uint8_t *validity, uint8_t lights)
{

    if (!getBit(lights, 5)) {                        
         if (getBit(lights, 3) && getBit(lights, 4))     //if hazards lights are not on, check that not both turn signals are on
        *validity &= ~0b00000100;
    }                       

    int lowlights = getBit(lights, 1);
    int highlights = getBit(lights, 2);

    if (getBit(lights, 0)) {                        //if headlights are off, check all modes are off
        if (lowlights || highlights)
        *validity &= ~0b00000100;
    } else {                                        // if headlights are on, check that exactly one mode is on
        if (!lowlights && !highlights)
        *validity &= ~0b00000100;
        if (lowlights && highlights)               
        *validity &= ~0b00000100;
    }
}
