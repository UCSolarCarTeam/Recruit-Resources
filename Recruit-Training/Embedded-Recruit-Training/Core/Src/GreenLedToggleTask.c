#include "GreenLedToggleTask.h"
static const GREEN_LED_STATUS_STDID = 0xDDD;

void greenLedToggleTask(void const* arg)
{
    static const GREEN_LED_TOGGLE_FREQ = 10; //SET IT TO 10HZ SOMEHOW
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        osDelayUntil(prevWakeTime + GREEN_LED_TOGGLE_FREQ);  //TODO: Replace 1 with time period for delay
        //TODO: Check blue toggel flag and toggle blue LED
        if(greenFlag == 1)
        {
            //toggle blue led, this requires a HAL GPIO Function
        }
        //TODO: Send CAN message indicating current state of LED
        osStatus_t status = osMutexAcquire(canMutex, 1);
        while(status != osOK){
            status = osMutexAcquire(canMutex, 1);
        }

        //mutex aquired
        HAL_CAN_GetTxMailboxesFreeLevel(&hcan2); 
        uint8_t data[1] = {0};
        uint32_t mailbox; //should this be equal to the value HAL_CAN_GetTxMailboxesFreeLevel(hcan2) ? 
        CANTxHeader.StdId = GREEN_LED_STATUS_STDID;
        CANTxHeader.DLC = 1;
        //set element of data array to the current stauts of LED 
        //if GPIO Pin is 0 -> send a 1 (on)
        //if GPIO Pin is 1 -> send a 0 (off)
        HAL_CAN_AddTxMessage(&hcan2, &CANTxHeader, &data, &mailbox);
        //^ function returns HAl_StatusTypeDef
        osMutexRelease(canMutex); 


    }
}
