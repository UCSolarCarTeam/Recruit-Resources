#include "Training.h"

void trainingTask(uint8_t* data)
{
    loadMotorData(data[0], data[1]);
    loadLightData(data[2]);

    outputArray[0] = data[0];
    outputArray[1] = data[1];
    outputArray[2] = data[2];
    validData = 0b00000111;

    if(!checkMotors())
    {
        validData = 0b100 & validData;
    }
    if(!checkLights())
    {
        validData = 0b011 & validData;
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

bool checkMotors()
{
    //check power
    if(m1Power != m2Power){
        return false;
    }

    //check power vs movement
    if((m1Velocity != 0 && m1Power == 0) || (m1Power != 0 && m1Velocity == 0)){
        return false;
    }
    else if((m2Velocity != 0 && m2Power == 0) || (m2Power != 0 && m2Velocity == 0)){
        return false;
    }

    //check direction
    if(m1Velocity != 0 && (m1Direction == m1VelocitySign)){
        return false;
    }
    else if(m2Velocity != 0 && (m2Direction == m2VelocitySign)){
        return false;
    }

    //check synchronicity
    if(m1Direction != m2Direction) 
    {
        return false;
    } 
    else if (m1Velocity != m2Velocity)
    {
        return false;
    }

    return true;
}

bool checkLights()
{
    //check headlights
    if((headlightsOff + headlightsLow + headlightsHigh) != 1)
    {
        return false;
    }

    //check hazards and brakes
    if((hazards || brakes) && ((headlightsHigh + rightSignal + leftSignal) != 3))
    {
        return false;
    }
    
    //check signals
    if (!(hazards || brakes) && ((rightSignal + leftSignal) > 1))
    {
        return false;
    }

    return true;
}