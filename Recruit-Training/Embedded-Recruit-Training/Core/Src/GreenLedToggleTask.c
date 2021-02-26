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
        if(greenToggleFlag) 
        {
            HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_SET);
        } 
        else
        {
            HAL_GPIO_WritePin(GPIOA, LED_GREEN_Pin, GPIO_PIN_RESET);
        }

        //TODO: Send CAN message indicating current state of LED
        uint8_t GREEN_LED_STATUS_ID = HAL_GPIO_ReadPin(GPIOA, LED_GREEN_Pin);

        if(osMutexAcquire(canMutex, 0) == osOK)
        {
            uint32_t mailboxVariable = HAL_CAN_GetTxMailboxesFreeLevel(&hcan2); //unsure if this the right implementation

            canHeader.StdId = GREEN_LED_STATUS_STDID;
            canHeader.DLC = 1;
            uint8_t GREEN_LED_MESSAGE[1] = {(~GREEN_LED_STATUS_ID) & 0b0000000};
            
            if (HAL_CAN_AddTxMessage(&hcan2, &canHeader, GREEN_LED_MESSAGE, &mailboxVariable) != HAL_OK)
            {
                Error_Handler();
            }
            osMutexRelease(canMutex);
        }
    }
}
