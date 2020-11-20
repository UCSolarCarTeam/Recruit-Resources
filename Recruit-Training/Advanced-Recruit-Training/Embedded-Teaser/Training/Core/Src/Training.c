#include "Training.h"

void trainingTask(uint8_t* data)
{
  uint8_t motorsValid = checkMotors(data[0], data[1]);
  uint8_t lightsValid = checkLights(data[2]);

  if (motorsValid && lightsValid) // Everything valid so copy data and set all 3 bits of valid variable high
  {
    outputArray[0] = data[0];
    outputArray[1] = data[1];
    outputArray[2] = data[2];
    validData = 0b111;
  }
  else if (motorsValid) // Only motors valid so copy only data[0] and data[1] and set 2 LSBs high
  {
    outputArray[0] = data[0];
    outputArray[1] = data[1];
    validData = 0b011;
  }
  else if (lightsValid) // Only lights valid so copy only data[2] and set bit 3 high and the 2 LSBs low
  {
    outputArray[2] = data[2];
    validData = 0b100;
  }
  else
  {
    validData = 0b000;
  }
}

// Expands motor data into a struct
motorData_t extractMotorData(uint8_t motorData)
{
  motorData_t data;
  data.direction = motorData & 0x1; // Forward/reverse in bit 0
  data.on_off = (motorData >> 7) & 0x1; // On/off in bit 7

  // Get velocity
  uint8_t velocity_mag = (motorData >> 1) & 0x1F; // The magnitude is the bottom 5 bits of the velocity
  uint8_t velocity_sgn = (motorData >> 6) & 0x1; // The sign is bit 6

  data.velocity = velocity_sgn ? (velocity_mag * -1) : velocity_mag; // If sign is 1, the velocity is negative

  return data;
}

// Returns 1 if motor data is valid. 0 Otherwise
// Valid means:
//   - Motor 1 and Motor 2 must match in the following ways:
//      - If one is on, the other must be on. If one is off, the other must be off
//      - They must be going in the same direction
//   - Each individual motor is valid
//   - Motor 1 and 2 don't need to have the same velocity (could be turning)
uint8_t checkMotors(uint8_t motor1, uint8_t motor2)
{
  // Get motor data
  motorData_t motor1Data = extractMotorData(motor1);
  motorData_t motor2Data = extractMotorData(motor2);

  return (motor1Data.on_off == motor2Data.on_off) && // Both motors must have the same power state
         (motor1Data.direction == motor2Data.direction) && // Both motors must be going in the same direction
         checkMotor(motor1Data) && checkMotor(motor2Data); // Both motors must be valid
}

// Returns 1 if motor data is valid. 0 Otherwise
// Valid means:
//   - If the motor is going forward, the velocity must be positive or 0
//   - If the motor is going in reverse, the velocity must be negative or 0
//   - A motor must have 0 velocity if it's off
uint8_t checkMotor(motorData_t motor)
{
  return (motor.direction == 1 ? motor.velocity >= 0 : motor.velocity <= 0) && // Velocity must match the direction
         (motor.on_off == 0 ? motor.velocity == 0 : 1); // If motor is off, velocity must be 0
}

// Returns 1 if lights data is valid. 0 Otherwise
// Valid means:
//  - Only one of headlights off, headlights low, and headlights high can be 1 and one of them must be 1
//  - If hazards are on, the left and right signal must be on at the same time
//  - If hazards are off, only one of left and right signal can be on or both can be off
uint8_t checkLights(uint8_t lights)
{
  uint8_t headlightsOff = lights & 0x1;
  uint8_t headlightsLow = (lights >> 1) & 0x1;
  uint8_t headlightsHigh = (lights >> 2) & 0x1;
  uint8_t rightSignal = (lights >> 3) & 0x1;
  uint8_t leftSignal = (lights >> 4) & 0x1;
  uint8_t hazards = (lights >> 5) & 0x1;
  uint8_t brakes = (lights >> 6) & 0x1;

  // Check headlights
  if(headlightsOff == 1)
  {
    if(headlightsLow || headlightsHigh) return 0;
  }
  else if(headlightsLow == 1)
  {
    if(headlightsOff || headlightsHigh) return 0;
  }
  else if(headlightsHigh == 1)
  {
    if(headlightsLow || headlightsOff) return 0;
  }
  else
  {
    return 0;
  }

  // Check hazards and signals
  if(hazards)
  {
    if(!(rightSignal && leftSignal)) return 0;
  }
  else
  {
    if(rightSignal && leftSignal) return 0;
  }

  return 1;
}
