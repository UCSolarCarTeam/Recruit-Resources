#include "Training.h"

void trainingTask(uint8_t* data)
{
    loadMotorData(data[0], data[1]);
    loadLightData(data[2]);

    validData = 0b0;

    if(motorsValid())
    {
        outputArray[0] = data[0];
        outputArray[1] = data[1];
        validData = 0b11;
    }

    if(lightsValid())
    {
        outputArray[2] = data[2];
        validData = 0b100 | validData;
    }
}

void loadMotorData(uint8_t m1, uint8_t m2)
{
    m1Direction = m1 & 0b00000001;
    m2Direction = m2 & 0b00000001;

    m1VelocitySign = (m1 >> 6) & 0b00000001;
    m2VelocitySign = (m2 >> 6) & 0b00000001;

    m1Velocity = (m1 >> 1) & 0b00011111;
    if(m1VelocitySign)
    { 
        m1Velocity *= -1;
    }

    m2Velocity = (m2 >> 1) & 0b00011111;
    if(m2VelocitySign) 
    {
        m2Velocity *= -1;
    }

    m1Power = m1 >> 7;
    m2Power = m2 >> 7;
}

void loadLightData(uint8_t lights)
{
    headlightsOff = lights & 0b00000001;
    headlightsLow = (lights >> 1) & 0b00000001;
    headlightsHigh = (lights >> 2) & 0b00000001;

    rightSignal = (lights >> 3) & 0b00000001;
    leftSignal = (lights >> 4) & 0b00000001;

    hazards = (lights >> 5) & 0b00000001;
    brakes = (lights >> 6) & 0b00000001;
}

uint8_t motorsValid()
{
    //check power
    if((m1Power + m2Power) == 1){
        return 0;
    }

    //check power vs movement
    if((m1Velocity != 0 && m1Power == 0) || (m1Power != 0 && m1Velocity == 0)){
        return 0;
    }
    else if((m2Velocity != 0 && m2Power == 0) || (m2Power != 0 && m2Velocity == 0)){
        return 0;
    }

    //check direction
    if(m1Velocity != 0 && (m1Direction == m1VelocitySign)){
        return 0;
    }
    else if(m2Velocity != 0 && (m2Direction == m2VelocitySign)){
        return 0;
    }

    //check synchronicity
    if(m1Direction != m2Direction) 
    {
        return 0;
    } 
    else if (m1Velocity != m2Velocity)
    {
        return 0;
    }

    return 1;
}

uint8_t lightsValid()
{
    /**
     * Here, we are checking if the headlights are valid, meaning only one headlight setting is on (value = 1)
     * Therefore, if we add up all of the headlight setting variables, it should total to 1
     * If not, then there is something wrong with the headlights data and return
     */
    if((headlightsOff + headlightsLow + headlightsHigh) != 1)
    {
        return 0;
    }


    if(hazards || brakes) // Hazards and/or brakes are on
    {
        /**
         * If hazards and/or brakes are on, then to check if the lights are valid is if:
         *  1) right and left signals are on (meaning rightSignal = 1, leftSignal = 1)
         *  2) headlights are on high (meaning headlightsHigh = 1)
         * Therefore, headlightsHigh + rightSignal + leftSignal must equal 3 to be valid
         */
        if((headlightsHigh + rightSignal + leftSignal) != 3)
        {
            return 0;
        }
    }
    else // Neither hazards and/or brakes are on
    {
        /**
         * The only time when both signals can be on is if the hazards and/or brakes are on.
         * Since we have already checked that hazards and brakes are NOT on,
         * then rightSignal and leftSignal must not both be 1.
         * Therefore, if rightSignal + leftSignal == 2, then both signals are on and the signals are invalid. 
         */
        if((rightSignal + leftSignal) == 2)
        {
            return 0;
        }
    }

    return 1;
}
