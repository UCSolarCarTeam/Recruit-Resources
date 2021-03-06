#include "BlueLedToggleTask.h"

void blueLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg; // Get mutex that was passed as an argument

    static const uint32_t BLUE_LED_STATUS_STDID = 0xCCC;
    static const uint32_t BLUE_LED_TOGGLE_FREQ = 1000;


    for (;;)
    {
        //TODO: Add BLUE_LED_TOGGLE_FREQ to prevWakeTime
        prevWakeTime += BLUE_LED_TOGGLE_FREQ;
        osDelayUntil(prevWakeTime);

        //TODO: Check blue toggle flag and toggle blue LED
        if(blueLedToggleFlag) 
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        }

        //TODO: Send CAN message indicating current state of LED
        uint8_t blueLedStatusId = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);

        if(osMutexAcquire(canMutex, 0) == osOK)
        {
            uint32_t mailboxVariable = HAL_CAN_GetTxMailboxesFreeLevel(&hcan2);
            if(mailboxVariable != 0U)
            {
                canHeader.StdId = BLUE_LED_STATUS_STDID;
                canHeader.DLC = 1;
                uint8_t blueLedMessage[1] = {blueLedStatusId ^ 0b0000001};
            
                if (HAL_CAN_AddTxMessage(&hcan2, &canHeader, blueLedMessage, &mailboxVariable) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            osMutexRelease(canMutex);
        }
    }
}
