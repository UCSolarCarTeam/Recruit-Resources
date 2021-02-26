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
        if(blueToggleFlag) 
        {
            HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOA, LED_RED_Pin, GPIO_PIN_RESET);
        }

        //TODO: Send CAN message indicating current state of LED
        uint8_t BLUE_LED_STATUS_ID = HAL_GPIO_ReadPin(GPIOA, LED_RED_Pin);

        if(osMutexAcquire(canMutex, 0) == osOK)
        {
            uint32_t mailboxVariable = HAL_CAN_GetTxMailboxesFreeLevel(&hcan2); // unsure if this the right implementation

            canHeader.StdId = BLUE_LED_STATUS_STDID;
            canHeader.DLC = 1;
            uint8_t BLUE_LED_MESSAGE[1] = {(~BLUE_LED_STATUS_ID) & 0b0000000};
            
            if (HAL_CAN_AddTxMessage(&hcan2, &canHeader, BLUE_LED_MESSAGE, &mailboxVariable) != HAL_OK)
            {
                Error_Handler();
            }
            osMutexRelease(canMutex);
        }
    }
}
