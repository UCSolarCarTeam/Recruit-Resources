#include "GreenLedToggleTask.h"

void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
    static const uint32_t GREEN_LED_TOGGLE_FREQ = 100;

    for (;;)
    {
        //TODO: Add GREEN_LED_TOGGLE_FREQ to prevWakeTime
        prevWakeTime += GREEN_LED_TOGGLE_FREQ;
        osDelayUntil(prevWakeTime);

        //TODO: Check green toggle flag and toggle green LED
        if(greenLedToggleFlag) 
        {
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        } 

        //TODO: Send CAN message indicating current state of LED
        uint8_t greenLedStatusId = HAL_GPIO_ReadPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);

        if(osMutexAcquire(canMutex, 0) == osOK)
        {
            if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint32_t mailboxVariable;
                canHeader.StdId = GREEN_LED_STATUS_STDID;
                canHeader.DLC = 1;
                uint8_t greenLedMessage[1] = {greenLedStatusId ^ 0b00000001};
            
                if (HAL_CAN_AddTxMessage(&hcan2, &canHeader, greenLedMessage, &mailboxVariable) != HAL_OK)
                {
                    Error_Handler();
                }
            }
            osMutexRelease(canMutex);
        }
    }
}
