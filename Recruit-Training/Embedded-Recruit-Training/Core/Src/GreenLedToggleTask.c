#include "GreenLedToggleTask.h"

void greenLedToggleTask(void const* arg)
{
    extern CAN_HandleTypeDef hcan2;
    extern CAN_TxHeaderTypeDef CAN_TX;
    extern uint8_t GreenToggleFlag;
    
    //One time osDelayUntil initialization
    static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
    static const uint32_t GREEN_LED_TOGGLE_FREQ = 100;
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        //TODO: Add GREEN_LED_TOGGLE_FREQ to prevWakeTime
        prevWakeTime += GREEN_LED_TOGGLE_FREQ;
        osDelayUntil(prevWakeTime);
        //TODO: Check blue toggel flag and toggle blue LED
        if (GreenToggleFlag)
        {
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        }

        uint8_t ledState = HAL_GPIO_ReadPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        //TODO: Send CAN message indicating current state of LED

        if (osMutexAcquire(canMutex, 0) == osOK)
        {
            if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
            uint8_t currentLedStatus[1];
            uint32_t mailbox;
            CAN_TX.StdId = GREEN_LED_STATUS_STDID;
            CAN_TX.DLC = 1;
            currentLedStatus[0] = !ledState;
            HAL_CAN_AddTxMessage(&hcan2, &CAN_TX, currentLedStatus, &mailbox);
            }
            osMutexRelease(canMutex);
        }
    }
}
