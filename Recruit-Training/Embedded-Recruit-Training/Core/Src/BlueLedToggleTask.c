#include "BlueLedToggleTask.h"

static const uint32_t BLUE_LED_STATUS_STDID = 0xCCC;
static const uint32_t BLUE_LED_TOGGLE_FREQ = 1000;

void blueLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg; // Get mutex that was passed as an argument

    for (;;)
    {
        prevWakeTime += BLUE_LED_TOGGLE_FREQ;
        osDelayUntil(prevWakeTime);  //TODO: Replace 1 with time period for delay
        
        //TODO: Check blue toggle flag and toggle blue LED
        if (blueToggleFlag)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        }
        
        GPIO_PinState blueStatus = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);

        //TODO: Send CAN message indicating current state of LED
        if (osMutexAcquire(canMutex, 0) != osOK) continue;

        if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2))
        {
            uint8_t data[1] = {0};
            uint32_t mailbox;
            
            CAN_TxHeader.StdId = BLUE_LED_STATUS_STDID;
            CAN_TxHeader.DLC = 1;
                
            data[0] = !blueStatus;
            HAL_CAN_AddTxMessage(&hcan2, &CAN_TxHeader, &data, &mailbox);
        }
        
        osMutexRelease(canMutex);
    }
}
