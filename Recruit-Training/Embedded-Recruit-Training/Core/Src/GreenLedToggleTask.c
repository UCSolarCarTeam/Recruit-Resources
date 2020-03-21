#include "GreenLedToggleTask.h"
static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
static const uint32_t GREEN_LED_TOGGLE_FREQ = 100000;

void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        osDelayUntil(prevWakeTime + GREEN_LED_TOGGLE_FREQ);  //TODO: Replace 1 with time period for delay
        //TODO: Check blue toggel flag and toggle blue LED
        if(greenFlag == 1)
        {
            //toggle green led, this requires a HAL GPIO Function
            HAL_GPIO_TogglePin(GPIOA, LED_GREEN_Pin);
        }
        uint8_t greenLedVal = HAL_GPIO_ReadPin(GPIOA, LED_GREEN_Pin);
        //TODO: Send CAN message indicating current state of LED;

        if(osMutexAcquire(canMutex, 0) == osOK)
        {
            if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint8_t data[1] = {0};
                uint32_t mailbox; 
                CANTxHeader.StdId = GREEN_LED_STATUS_STDID;
                CANTxHeader.DLC = 1;
                
                data[0] = !greenLedVal;

                HAL_CAN_AddTxMessage(&hcan2, &CANTxHeader, &data, &mailbox);
                osMutexRelease(canMutex);
            }
        
            osMutexRelease(canMutex); 
        }
        else
        {
            continue;
        }
    }
}
