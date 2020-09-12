#include "BlueLedToggleTask.h"

void blueLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    static const uint32_t BLUE_LED_STATUS_STDID = 0xCCC;
    static const uint32_t BLUE_LED_TOGGLE_FREQ = 100;
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg; // Get mutex that was passed as an argument

    for (;;)
    {
        //TODO: Add BLUE_LED_TOGGLE_FREQ to prevWakeTime
        osDelayUntil(prevWakeTime);
        prevWakeTime += BLUE_LED_TOGGLE_FREQ;
        //TODO: Check blue toggle flag and toggle blue LED
        if (BlueToggleFlag)
        {
            HAL_GPIO_TogglePin( LED_RED_GPIO_Port, LED_RED_Pin);
        }
        
        uint8_t ledState = HAL_GPIO_ReadPin( LED_RED_GPIO_Port, LED_RED_Pin);
        //TODO: Send CAN message indicating current state of LED

        if (osMutexAcquire(canMutex, 0) == osOK)
        {
            if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
            uint8_t x[1];
            uint32_t mailbox;
            CAN_TX.StdId = BLUE_LED_STATUS_STDID;
            CAN_TX.DLC = 1;
            x[0] = !ledState;
            HAL_CAN_AddTxMessage(&hcan2, &CAN_TX, x, &mailbox);
            }
            osMutexRelease(canMutex);
        }
    }
}




