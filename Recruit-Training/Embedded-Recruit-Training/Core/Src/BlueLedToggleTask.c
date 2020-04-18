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
        osDelayUntil(prevWakeTime);

        if (blueLedToggleFlag)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
        }

        uint8_t blueLedVal = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);

        if (osMutexAcquire(canMutex, 0) == osOK)
        {
            if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint8_t data[1];
                uint32_t mailbox;

                canTxHdr.StdId = BLUE_LED_STATUS_STDID;
                canTxHdr.DLC = 1;

                data[0] = !blueLedVal;

                HAL_CAN_AddTxMessage(&hcan2, &canTxHdr, data, &mailbox);
            }

            osMutexRelease(canMutex);
        }
    }
}
