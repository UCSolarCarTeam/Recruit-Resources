#include "GreenLedToggleTask.h"

static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
static const uint32_t GREEN_LED_TOGGLE_FREQ = 100;


void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        osDelayUntil(prevWakeTime + GREEN_LED_TOGGLE_FREQ);

        if (greenLedToggleFlag)
        {
            HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        }

        uint8_t greenLedVal = HAL_GPIO_ReadPin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);

        if (osMutexAcquire(canMutex, 0) == osOK)
        {
            if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint8_t data[1];
                uint32_t mailbox;

                canTxHdr.StdId = GREEN_LED_STATUS_STDID;
                canTxHdr.DLC = 1;

                data[0] = !greenLedVal;

                HAL_CAN_AddTxMessage(&hcan2, &canTxHdr, data, &mailbox);
            }

            osMutexRelease(canMutex);
        }

    }
}
