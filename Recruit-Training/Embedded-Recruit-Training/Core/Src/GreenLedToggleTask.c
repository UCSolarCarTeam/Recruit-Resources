#include "GreenLedToggleTask.h"

static const uint32_t GREEN_LED_STATUS_STDID = 0xDDD;
static const uint32_t GREEN_LED_TOGGLE_FREQ = 10000;

void greenLedToggleTask(void const* arg)
{
    //One time osDelayUntil initialization
    uint32_t prevWakeTime = osKernelSysTick();

    osMutexId_t* canMutex = (osMutexId_t*)arg;

    for (;;)
    {
        //TODO: Add GREEN_LED_TOGGLE_FREQ to prevWakeTime
        preWakeTime += GREEN_LED_TOGGLE_FREQ;
        osDelayUntil(prevWakeTime);

        //TODO: Check blue toggel flag and toggle blue LED

        if(GreenToggleLED)
        {
            HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
            
        }

        uint8_t pinState_of_green_LED = HAL_GPIO_ReadPin(LED_RED_GPIO_Port, LED_RED_Pin);
        //TODO: Send CAN message indicating current state of LED

        if(osMutexAcquire(canMutex, 0))
        {
            if(HAL_CAN_GetTxMailboxesFreeLevel(&hcan2) > 0)
            {
                uint8_t data_array_green[1];

                uint32_t mailbox_variable_green;

                CANTxHeader.StdId = GREEN_LED_STATUS_STDID;
                CANTxHeader.DLC = 1;
                data_array_green[0] = !pinState_of_green_LED;

                HAL_CAN_AddTxMessage(&hcan2, &CANTxHeader, &data_array_green, &mailbox_variable_green);
                osMutexRelease(canMutex);

            }
        
        }

    }
}
